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
struct pcm_channel {int /*<<< orphan*/  bufhard; int /*<<< orphan*/  devinfo; int /*<<< orphan*/  methods; } ;

/* Variables and functions */
 int CHANNEL_GETPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHN_LOCKASSERT (struct pcm_channel*) ; 
 scalar_t__ CHN_STARTED (struct pcm_channel*) ; 
 int sndbuf_getalign (int /*<<< orphan*/ ) ; 

int
chn_getptr(struct pcm_channel *c)
{
	int hwptr;

	CHN_LOCKASSERT(c);
	hwptr = (CHN_STARTED(c)) ? CHANNEL_GETPTR(c->methods, c->devinfo) : 0;
	return (hwptr - (hwptr % sndbuf_getalign(c->bufhard)));
}