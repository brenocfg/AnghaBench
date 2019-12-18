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

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lwp_getprivate () ; 
 scalar_t__ alter_tlsbase ; 
 int /*<<< orphan*/  nctx ; 
 int /*<<< orphan*/  ntls ; 
 int /*<<< orphan*/  octx ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val1 ; 
 int /*<<< orphan*/  val2 ; 

__attribute__((used)) static void
swapfunc(void *arg)
{
	ntls = _lwp_getprivate();
	printf("after swapcontext TLS pointer = %p\n", ntls);

	if (alter_tlsbase) {
		ATF_REQUIRE_EQ(ntls, &val1);
		printf("TLS pointer modified by swapcontext()\n");
	} else {
		ATF_REQUIRE_EQ(ntls, &val2);
		printf("TLS pointer left untouched by swapcontext()\n");
	}

	/* Go back in main */
	ATF_REQUIRE(swapcontext(&nctx, &octx));

	/* NOTREACHED */
	return;
}