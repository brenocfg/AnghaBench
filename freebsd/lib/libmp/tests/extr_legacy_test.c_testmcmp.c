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
 scalar_t__ mp_mcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  printf (char*,int,char const*) ; 
 int tnr ; 

__attribute__((used)) static void
testmcmp(const MINT *mp1, const MINT *mp2, const char *tname)
{

	if (mp_mcmp(mp1, mp2) == 0)
		printf("ok %d - %s\n", ++tnr, tname);
	else
		printf("not ok - %d %s\n", ++tnr, tname);
}