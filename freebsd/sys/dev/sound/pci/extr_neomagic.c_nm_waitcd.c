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
struct sc_info {int ac97_busy; int /*<<< orphan*/  ac97_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int nm_rd (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nm_waitcd(struct sc_info *sc)
{
	int cnt = 10;
	int fail = 1;

	while (cnt-- > 0) {
		if (nm_rd(sc, sc->ac97_status, 2) & sc->ac97_busy) {
			DELAY(100);
		} else {
			fail = 0;
			break;
		}
	}
	return (fail);
}