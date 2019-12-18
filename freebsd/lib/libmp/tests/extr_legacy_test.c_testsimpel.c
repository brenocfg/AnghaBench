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
 int /*<<< orphan*/ * c42 ; 
 int /*<<< orphan*/ * c43 ; 
 int /*<<< orphan*/ * c44 ; 
 int /*<<< orphan*/  mp_madd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_mfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_msub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mp_mtox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_xtom (char const*) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * t0 ; 
 int /*<<< orphan*/  testmcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int tnr ; 

__attribute__((used)) static void
testsimpel(void)
{
	const char str42[] = "2a";
	MINT *t2;
	char *s;

	mp_madd(c42, c1, t0);
	testmcmp(c43, t0, "madd0");
	mp_madd(t0, c1, t0);
	testmcmp(c44, t0, "madd1");
	mp_msub(t0, c1, t0);
	testmcmp(c43, t0, "msub0");
	mp_msub(t0, c1, t0);
	testmcmp(c42, t0, "msub1");
	mp_move(c42, t0);
	testmcmp(c42, t0, "move0");

	t2 = mp_xtom(str42);
	testmcmp(c42, t2, "xtom");
	s = mp_mtox(t2);
	if (strcmp(str42, s) == 0)
		printf("ok %d - %s\n", ++tnr, "mtox0");
	else
		printf("not ok %d - %s\n", ++tnr, "mtox0");
	mp_mfree(t2);
}