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
struct pll_sc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int PLL_LOCK_TIMEOUT ; 
 scalar_t__ is_locked (struct pll_sc*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
wait_for_lock(struct pll_sc *sc)
{
	int i;

	for (i = PLL_LOCK_TIMEOUT / 10; i > 0; i--) {
		if (is_locked(sc))
			break;
		DELAY(10);
	}
	if (i <= 0) {
		printf("PLL lock timeout\n");
		return (ETIMEDOUT);
	}
	return (0);
}