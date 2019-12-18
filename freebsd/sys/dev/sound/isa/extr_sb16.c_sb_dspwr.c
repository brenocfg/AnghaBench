#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ td_intr_nesting_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SBDSP_CMD ; 
 int /*<<< orphan*/  SBDSP_STATUS ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sb_rd (struct sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_wr (struct sb_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sb_dspwr(struct sb_info *sb, u_char val)
{
    	int  i;

    	for (i = 0; i < 1000; i++) {
		if ((sb_rd(sb, SBDSP_STATUS) & 0x80))
	    		DELAY((i > 100)? 1000 : 10);
	    	else {
			sb_wr(sb, SBDSP_CMD, val);
			return 1;
		}
    	}
	if (curthread->td_intr_nesting_level == 0)
		printf("sb_dspwr(0x%02x) timed out.\n", val);
    	return 0;
}