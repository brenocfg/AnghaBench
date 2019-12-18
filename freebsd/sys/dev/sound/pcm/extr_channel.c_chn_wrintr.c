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
 int /*<<< orphan*/  PCMTRIG_EMLDMAWR ; 
 int /*<<< orphan*/  chn_dmaupdate (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_trigger (struct pcm_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chn_wrfeed (struct pcm_channel*) ; 

__attribute__((used)) static void
chn_wrintr(struct pcm_channel *c)
{

	CHN_LOCKASSERT(c);
	/* update pointers in primary buffer */
	chn_dmaupdate(c);
	/* ...and feed from secondary to primary */
	chn_wrfeed(c);
	/* tell the driver we've updated the primary buffer */
	chn_trigger(c, PCMTRIG_EMLDMAWR);
}