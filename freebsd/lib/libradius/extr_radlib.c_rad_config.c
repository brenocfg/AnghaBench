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
struct rad_handle {int /*<<< orphan*/  errmsg; int /*<<< orphan*/  type; } ;
struct in_addr {scalar_t__ s_addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned long DEAD_TIME ; 
 int ERRSIZE ; 
 scalar_t__ INADDR_ANY ; 
 scalar_t__ INADDR_NONE ; 
 int MAXCONFLINE ; 
 unsigned long MAXTRIES ; 
 int MAX_FIELDS ; 
 char* PATH_RADIUS_CONF ; 
 int /*<<< orphan*/  RADIUS_AUTH ; 
 unsigned long TIMEOUT ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*,char const*,int,...) ; 
 scalar_t__ inet_addr (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int rad_add_server_ex (struct rad_handle*,char*,int,char*,unsigned long,unsigned long,unsigned long,struct in_addr*) ; 
 int split (char*,char**,int,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 void* strtoul (char*,char**,int) ; 

int
rad_config(struct rad_handle *h, const char *path)
{
	FILE *fp;
	char buf[MAXCONFLINE];
	int linenum;
	int retval;

	if (path == NULL)
		path = PATH_RADIUS_CONF;
	if ((fp = fopen(path, "r")) == NULL) {
		generr(h, "Cannot open \"%s\": %s", path, strerror(errno));
		return -1;
	}
	retval = 0;
	linenum = 0;
	while (fgets(buf, sizeof buf, fp) != NULL) {
		int len;
		char *fields[MAX_FIELDS];
		int nfields;
		char msg[ERRSIZE];
		char *type;
		char *host, *res;
		char *port_str;
		char *secret;
		char *timeout_str;
		char *maxtries_str;
		char *dead_time_str;
		char *bindto_str;
		char *end;
		char *wanttype;
		unsigned long timeout;
		unsigned long maxtries;
		unsigned long dead_time;
		int port;
		struct in_addr bindto;
		int i;

		linenum++;
		len = strlen(buf);
		/* We know len > 0, else fgets would have returned NULL. */
		if (buf[len - 1] != '\n') {
			if (len == sizeof buf - 1)
				generr(h, "%s:%d: line too long", path,
				    linenum);
			else
				generr(h, "%s:%d: missing newline", path,
				    linenum);
			retval = -1;
			break;
		}
		buf[len - 1] = '\0';

		/* Extract the fields from the line. */
		nfields = split(buf, fields, MAX_FIELDS, msg, sizeof msg);
		if (nfields == -1) {
			generr(h, "%s:%d: %s", path, linenum, msg);
			retval = -1;
			break;
		}
		if (nfields == 0)
			continue;
		/*
		 * The first field should contain "auth" or "acct" for
		 * authentication or accounting, respectively.  But older
		 * versions of the file didn't have that field.  Default
		 * it to "auth" for backward compatibility.
		 */
		if (strcmp(fields[0], "auth") != 0 &&
		    strcmp(fields[0], "acct") != 0) {
			if (nfields >= MAX_FIELDS) {
				generr(h, "%s:%d: invalid service type", path,
				    linenum);
				retval = -1;
				break;
			}
			nfields++;
			for (i = nfields;  --i > 0;  )
				fields[i] = fields[i - 1];
			fields[0] = "auth";
		}
		if (nfields < 3) {
			generr(h, "%s:%d: missing shared secret", path,
			    linenum);
			retval = -1;
			break;
		}
		type = fields[0];
		host = fields[1];
		secret = fields[2];
		timeout_str = fields[3];
		maxtries_str = fields[4];
		dead_time_str = fields[5];
		bindto_str = fields[6];

		/* Ignore the line if it is for the wrong service type. */
		wanttype = h->type == RADIUS_AUTH ? "auth" : "acct";
		if (strcmp(type, wanttype) != 0)
			continue;

		/* Parse and validate the fields. */
		res = host;
		host = strsep(&res, ":");
		port_str = strsep(&res, ":");
		if (port_str != NULL) {
			port = strtoul(port_str, &end, 10);
			if (*end != '\0') {
				generr(h, "%s:%d: invalid port", path,
				    linenum);
				retval = -1;
				break;
			}
		} else
			port = 0;
		if (timeout_str != NULL) {
			timeout = strtoul(timeout_str, &end, 10);
			if (*end != '\0') {
				generr(h, "%s:%d: invalid timeout", path,
				    linenum);
				retval = -1;
				break;
			}
		} else
			timeout = TIMEOUT;
		if (maxtries_str != NULL) {
			maxtries = strtoul(maxtries_str, &end, 10);
			if (*end != '\0') {
				generr(h, "%s:%d: invalid maxtries", path,
				    linenum);
				retval = -1;
				break;
			}
		} else
			maxtries = MAXTRIES;

		if (dead_time_str != NULL) {
			dead_time = strtoul(dead_time_str, &end, 10);
			if (*end != '\0') {
				generr(h, "%s:%d: invalid dead_time", path,
				    linenum);
				retval = -1;
				break;
			}
		} else
		    	dead_time = DEAD_TIME;

		if (bindto_str != NULL) {
		    	bindto.s_addr = inet_addr(bindto_str);
			if (bindto.s_addr == INADDR_NONE) {
				generr(h, "%s:%d: invalid bindto", path,
				    linenum);
				retval = -1;
				break;
			}
		} else
		    	bindto.s_addr = INADDR_ANY;

		if (rad_add_server_ex(h, host, port, secret, timeout, maxtries,
			    dead_time, &bindto) == -1) {
			strcpy(msg, h->errmsg);
			generr(h, "%s:%d: %s", path, linenum, msg);
			retval = -1;
			break;
		}
	}
	/* Clear out the buffer to wipe a possible copy of a shared secret */
	memset(buf, 0, sizeof buf);
	fclose(fp);
	return retval;
}