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
struct pcm_channel {int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int CHANNEL_GETRATES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

int
chn_getrates(struct pcm_channel *c, int **rates)
{
	KASSERT(rates != NULL, ("rates is null"));
	CHN_LOCKASSERT(c);
	return CHANNEL_GETRATES(c->methods, c->devinfo, rates);
}