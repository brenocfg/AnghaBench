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
typedef  int /*<<< orphan*/  u_long ;
struct rpcent {int /*<<< orphan*/  r_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct rpcent* getrpcbyname (char*) ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static u_long
getprognum (char *arg)
{
	char *strptr;
	register struct rpcent *rpc;
	register u_long prognum;
	char *tptr = arg;

	while (*tptr && isdigit(*tptr++));
	if (*tptr || isalpha(*(tptr - 1))) {
		rpc = getrpcbyname(arg);
		if (rpc == NULL)
			errx(1, "%s is unknown service", arg);
		prognum = rpc->r_number;
	} else {
		prognum = strtol(arg, &strptr, 10);
		if (strptr == arg || *strptr != '\0')
			errx(1, "%s is illegal program number", arg);
	}
	return (prognum);
}