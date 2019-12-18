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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr_storage {int dummy; } ;
struct delegpt {int has_parent_side_NS; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  authextstrtoaddr (char*,struct sockaddr_storage*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  delegpt_add_addr_mlc (struct delegpt*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  delegpt_add_ns_mlc (struct delegpt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct delegpt* delegpt_create_mlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delegpt_free_mlc (struct delegpt*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 char* skipwhite (char*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,...) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static struct delegpt*
parse_delegpt(RES* ssl, char* args, uint8_t* nm, int allow_names)
{
	/* parse args and add in */
	char* p = args;
	char* todo;
	struct delegpt* dp = delegpt_create_mlc(nm);
	struct sockaddr_storage addr;
	socklen_t addrlen;
	char* auth_name;
	if(!dp) {
		(void)ssl_printf(ssl, "error out of memory\n");
		return NULL;
	}
	while(p) {
		todo = p;
		p = strchr(p, ' '); /* find next spot, if any */
		if(p) {
			*p++ = 0;	/* end this spot */
			p = skipwhite(p); /* position at next spot */
		}
		/* parse address */
		if(!authextstrtoaddr(todo, &addr, &addrlen, &auth_name)) {
			if(allow_names) {
				uint8_t* n = NULL;
				size_t ln;
				int lb;
				if(!parse_arg_name(ssl, todo, &n, &ln, &lb)) {
					(void)ssl_printf(ssl, "error cannot "
						"parse IP address or name "
						"'%s'\n", todo);
					delegpt_free_mlc(dp);
					return NULL;
				}
				if(!delegpt_add_ns_mlc(dp, n, 0)) {
					(void)ssl_printf(ssl, "error out of memory\n");
					free(n);
					delegpt_free_mlc(dp);
					return NULL;
				}
				free(n);

			} else {
				(void)ssl_printf(ssl, "error cannot parse"
					" IP address '%s'\n", todo);
				delegpt_free_mlc(dp);
				return NULL;
			}
		} else {
#if ! defined(HAVE_SSL_SET1_HOST) && ! defined(HAVE_X509_VERIFY_PARAM_SET1_HOST)
			if(auth_name)
			  log_err("no name verification functionality in "
				"ssl library, ignored name for %s", todo);
#endif
			/* add address */
			if(!delegpt_add_addr_mlc(dp, &addr, addrlen, 0, 0,
				auth_name)) {
				(void)ssl_printf(ssl, "error out of memory\n");
				delegpt_free_mlc(dp);
				return NULL;
			}
		}
	}
	dp->has_parent_side_NS = 1;
	return dp;
}