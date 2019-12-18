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
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  addr_mask (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  ipstrtoaddr (char*,int,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 scalar_t__ str_is_ip6 (char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int netblockstrtoaddr(const char* str, int port, struct sockaddr_storage* addr,
        socklen_t* addrlen, int* net)
{
	char buf[64];
	char* s;
	*net = (str_is_ip6(str)?128:32);
	if((s=strchr(str, '/'))) {
		if(atoi(s+1) > *net) {
			log_err("netblock too large: %s", str);
			return 0;
		}
		*net = atoi(s+1);
		if(*net == 0 && strcmp(s+1, "0") != 0) {
			log_err("cannot parse netblock: '%s'", str);
			return 0;
		}
		strlcpy(buf, str, sizeof(buf));
		s = strchr(buf, '/');
		if(s) *s = 0;
		s = buf;
	}
	if(!ipstrtoaddr(s?s:str, port, addr, addrlen)) {
		log_err("cannot parse ip address: '%s'", str);
		return 0;
	}
	if(s) {
		addr_mask(addr, *addrlen, *net);
	}
	return 1;
}