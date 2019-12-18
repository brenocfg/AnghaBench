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
struct ess_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DSP_DATA_AVAIL ; 
 int /*<<< orphan*/  DSP_READ ; 
 int ess_rd (struct ess_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ess_get_byte(struct ess_info *sc)
{
    	int i;

    	for (i = 1000; i > 0; i--) {
		if (ess_rd(sc, DSP_DATA_AVAIL) & 0x80)
			return ess_rd(sc, DSP_READ);
		else
			DELAY(20);
    	}
    	return -1;
}