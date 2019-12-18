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
struct delegpt {int dummy; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  find_arg2 (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_arg_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*,int*) ; 
 struct delegpt* parse_delegpt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int
parse_fs_args(RES* ssl, char* args, uint8_t** nm, struct delegpt** dp,
	int* insecure, int* prime)
{
	char* zonename;
	char* rest;
	size_t nmlen;
	int nmlabs;
	/* parse all -x args */
	while(args[0] == '+') {
		if(!find_arg2(ssl, args, &rest))
			return 0;
		while(*(++args) != 0) {
			if(*args == 'i' && insecure)
				*insecure = 1;
			else if(*args == 'p' && prime)
				*prime = 1;
			else {
				(void)ssl_printf(ssl, "error: unknown option %s\n", args);
				return 0;
			}
		}
		args = rest;
	}
	/* parse name */
	if(dp) {
		if(!find_arg2(ssl, args, &rest))
			return 0;
		zonename = args;
		args = rest;
	} else	zonename = args;
	if(!parse_arg_name(ssl, zonename, nm, &nmlen, &nmlabs))
		return 0;

	/* parse dp */
	if(dp) {
		if(!(*dp = parse_delegpt(ssl, args, *nm, 1))) {
			free(*nm);
			return 0;
		}
	}
	return 1;
}