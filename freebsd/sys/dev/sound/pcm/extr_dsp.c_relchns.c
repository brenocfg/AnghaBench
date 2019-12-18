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
typedef  int uint32_t ;
struct pcm_channel {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_UNLOCK (struct pcm_channel*) ; 
 int SD_F_PRIO_RD ; 
 int SD_F_PRIO_WR ; 

__attribute__((used)) static void
relchns(struct cdev *dev, struct pcm_channel *rdch, struct pcm_channel *wrch,
    uint32_t prio)
{
	if (wrch != NULL && (prio & SD_F_PRIO_WR))
		CHN_UNLOCK(wrch);
	if (rdch != NULL && (prio & SD_F_PRIO_RD))
		CHN_UNLOCK(rdch);
}