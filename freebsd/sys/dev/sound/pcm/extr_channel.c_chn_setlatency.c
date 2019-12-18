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
struct pcm_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int chn_resizebuf (struct pcm_channel*,int,int,int /*<<< orphan*/ ) ; 

int
chn_setlatency(struct pcm_channel *c, int latency)
{
	CHN_LOCKASSERT(c);
	/* Destroy blksz/blkcnt, enforce latency profile. */
	return chn_resizebuf(c, latency, -1, 0);
}