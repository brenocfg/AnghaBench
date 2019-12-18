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
typedef  int u_int32_t ;
struct agg_rchinfo {int stereo; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_CHANNEL (int) ; 
 int AFMT_S16_LE ; 
 int EINVAL ; 

__attribute__((used)) static int
aggrch_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct agg_rchinfo *ch = data;

	if (!(format & AFMT_S16_LE))
		return EINVAL;
	if (AFMT_CHANNEL(format) > 1)
		ch->stereo = 1;
	else
		ch->stereo = 0;
	return 0;
}