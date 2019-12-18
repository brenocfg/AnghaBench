#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connection_info {char* user; char* host; char* address; char* laddress; int lport; char* rdomain; } ;

/* Variables and functions */
 int a2port (char*) ; 
 int addr_match_list (char*,char*) ; 
 int /*<<< orphan*/  debug (char*,char*,...) ; 
 int /*<<< orphan*/  debug3 (char*,char*,...) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int match_cfg_line_group (char*,int,char*) ; 
 int match_hostname (char*,char*) ; 
 int match_pattern_list (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_test_missing_fatal (char*,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strdelim (char**) ; 

__attribute__((used)) static int
match_cfg_line(char **condition, int line, struct connection_info *ci)
{
	int result = 1, attributes = 0, port;
	char *arg, *attrib, *cp = *condition;

	if (ci == NULL)
		debug3("checking syntax for 'Match %s'", cp);
	else
		debug3("checking match for '%s' user %s host %s addr %s "
		    "laddr %s lport %d", cp, ci->user ? ci->user : "(null)",
		    ci->host ? ci->host : "(null)",
		    ci->address ? ci->address : "(null)",
		    ci->laddress ? ci->laddress : "(null)", ci->lport);

	while ((attrib = strdelim(&cp)) && *attrib != '\0') {
		attributes++;
		if (strcasecmp(attrib, "all") == 0) {
			if (attributes != 1 ||
			    ((arg = strdelim(&cp)) != NULL && *arg != '\0')) {
				error("'all' cannot be combined with other "
				    "Match attributes");
				return -1;
			}
			*condition = cp;
			return 1;
		}
		if ((arg = strdelim(&cp)) == NULL || *arg == '\0') {
			error("Missing Match criteria for %s", attrib);
			return -1;
		}
		if (strcasecmp(attrib, "user") == 0) {
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->user == NULL)
				match_test_missing_fatal("User", "user");
			if (match_pattern_list(ci->user, arg, 0) != 1)
				result = 0;
			else
				debug("user %.100s matched 'User %.100s' at "
				    "line %d", ci->user, arg, line);
		} else if (strcasecmp(attrib, "group") == 0) {
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->user == NULL)
				match_test_missing_fatal("Group", "user");
			switch (match_cfg_line_group(arg, line, ci->user)) {
			case -1:
				return -1;
			case 0:
				result = 0;
			}
		} else if (strcasecmp(attrib, "host") == 0) {
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->host == NULL)
				match_test_missing_fatal("Host", "host");
			if (match_hostname(ci->host, arg) != 1)
				result = 0;
			else
				debug("connection from %.100s matched 'Host "
				    "%.100s' at line %d", ci->host, arg, line);
		} else if (strcasecmp(attrib, "address") == 0) {
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->address == NULL)
				match_test_missing_fatal("Address", "addr");
			switch (addr_match_list(ci->address, arg)) {
			case 1:
				debug("connection from %.100s matched 'Address "
				    "%.100s' at line %d", ci->address, arg, line);
				break;
			case 0:
			case -1:
				result = 0;
				break;
			case -2:
				return -1;
			}
		} else if (strcasecmp(attrib, "localaddress") == 0){
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->laddress == NULL)
				match_test_missing_fatal("LocalAddress",
				    "laddr");
			switch (addr_match_list(ci->laddress, arg)) {
			case 1:
				debug("connection from %.100s matched "
				    "'LocalAddress %.100s' at line %d",
				    ci->laddress, arg, line);
				break;
			case 0:
			case -1:
				result = 0;
				break;
			case -2:
				return -1;
			}
		} else if (strcasecmp(attrib, "localport") == 0) {
			if ((port = a2port(arg)) == -1) {
				error("Invalid LocalPort '%s' on Match line",
				    arg);
				return -1;
			}
			if (ci == NULL) {
				result = 0;
				continue;
			}
			if (ci->lport == 0)
				match_test_missing_fatal("LocalPort", "lport");
			/* TODO support port lists */
			if (port == ci->lport)
				debug("connection from %.100s matched "
				    "'LocalPort %d' at line %d",
				    ci->laddress, port, line);
			else
				result = 0;
		} else if (strcasecmp(attrib, "rdomain") == 0) {
			if (ci == NULL || ci->rdomain == NULL) {
				result = 0;
				continue;
			}
			if (match_pattern_list(ci->rdomain, arg, 0) != 1)
				result = 0;
			else
				debug("user %.100s matched 'RDomain %.100s' at "
				    "line %d", ci->rdomain, arg, line);
		} else {
			error("Unsupported Match attribute %s", attrib);
			return -1;
		}
	}
	if (attributes == 0) {
		error("One or more attributes required for Match");
		return -1;
	}
	if (ci != NULL)
		debug3("match %sfound", result ? "" : "not ");
	*condition = cp;
	return result;
}