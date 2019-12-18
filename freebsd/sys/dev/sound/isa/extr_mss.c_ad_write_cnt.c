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
typedef  int u_short ;
struct mss_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_write (struct mss_info*,int,int) ; 

__attribute__((used)) static void
ad_write_cnt(struct mss_info *mss, int reg, u_short cnt)
{
    	ad_write(mss, reg+1, cnt & 0xff);
    	ad_write(mss, reg, cnt >> 8); /* upper base must be last */
}