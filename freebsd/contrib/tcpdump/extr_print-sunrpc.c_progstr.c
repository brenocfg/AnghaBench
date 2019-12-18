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
typedef  scalar_t__ uint32_t ;
struct rpcent {int /*<<< orphan*/  r_name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct rpcent* getrpcbynumber (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
progstr(uint32_t prog)
{
#if defined(HAVE_GETRPCBYNUMBER) && defined(HAVE_RPC_RPC_H)
	register struct rpcent *rp;
#endif
	static char buf[32];
	static uint32_t lastprog = 0;

	if (lastprog != 0 && prog == lastprog)
		return (buf);
#if defined(HAVE_GETRPCBYNUMBER) && defined(HAVE_RPC_RPC_H)
	rp = getrpcbynumber(prog);
	if (rp == NULL)
#endif
		(void) snprintf(buf, sizeof(buf), "#%u", prog);
#if defined(HAVE_GETRPCBYNUMBER) && defined(HAVE_RPC_RPC_H)
	else
		strlcpy(buf, rp->r_name, sizeof(buf));
#endif
	return (buf);
}