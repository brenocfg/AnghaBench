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
typedef  int /*<<< orphan*/  MINT ;

/* Variables and functions */
 int /*<<< orphan*/  c1 ; 
 int /*<<< orphan*/  c10 ; 
 int /*<<< orphan*/  c2 ; 
 int /*<<< orphan*/  c42 ; 
 int /*<<< orphan*/  c5 ; 
 int /*<<< orphan*/  c8 ; 
 int /*<<< orphan*/ * mp_itom (short) ; 
 int /*<<< orphan*/  mp_mdiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_sdiv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,short*) ; 
 int /*<<< orphan*/ * t0 ; 
 int /*<<< orphan*/ * t1 ; 
 int /*<<< orphan*/  testmcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
testdiv(void)
{
	short ro;
	MINT *t2;

	mp_mdiv(c42, c5, t0, t1);
	testmcmp(t0, c8, "mdiv0");
	testmcmp(t1, c2, "mdiv1");

	mp_mdiv(c10, c8, t0, t1);
	testmcmp(t0, c1, "mdiv2");
	testmcmp(t1, c2, "mdiv3");

	mp_sdiv(c42, 5, t0, &ro);
	testmcmp(t0, c8, "sdiv0");
	t2 = mp_itom(ro); // Simpler to use common testmcmp()
	testmcmp(t2, c2, "sdiv1");
	mp_mfree(t2);

	mp_sdiv(c10, 8, t0, &ro);
	testmcmp(t0, c1, "sdiv2");
	t2 = mp_itom(ro); // Simpler to use common testmcmp()
	testmcmp(t2, c2, "sdiv3");
	mp_mfree(t2);
}