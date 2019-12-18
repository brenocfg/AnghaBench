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
typedef  int u_char ;
struct sb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SBDSP_CMD ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ sb_dspready (struct sb_info*) ; 
 int /*<<< orphan*/  sb_wr (struct sb_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sb_dspwr(struct sb_info *sb, u_char val)
{
    	int  i;

    	for (i = 0; i < 1000; i++) {
		if (sb_dspready(sb)) {
	    		sb_wr(sb, SBDSP_CMD, val);
	    		return 1;
		}
		if (i > 10) DELAY((i > 100)? 1000 : 10);
    	}
    	printf("sb_dspwr(0x%02x) timed out.\n", val);
    	return 0;
}