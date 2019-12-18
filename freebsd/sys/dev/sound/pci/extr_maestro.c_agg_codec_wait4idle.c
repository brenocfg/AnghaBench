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
struct agg_info {int dummy; } ;

/* Variables and functions */
 int AGG_RD (struct agg_info*,int /*<<< orphan*/ ,int) ; 
 int CODEC_STAT_MASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  PORT_CODEC_STAT ; 

__attribute__((used)) static int
agg_codec_wait4idle(struct agg_info *ess)
{
	unsigned t = 26;

	while (AGG_RD(ess, PORT_CODEC_STAT, 1) & CODEC_STAT_MASK) {
		if (--t == 0)
			return EBUSY;
		DELAY(2);	/* 20.8us / 13 */
	}
	return 0;
}