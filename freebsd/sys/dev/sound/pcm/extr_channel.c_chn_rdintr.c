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
 int /*<<< orphan*/  PCMTRIG_EMLDMARD ; 
 int /*<<< orphan*/  chn_dmaupdate (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_rdfeed (struct pcm_channel*) ; 
 int /*<<< orphan*/  chn_trigger (struct pcm_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chn_rdintr(struct pcm_channel *c)
{

	CHN_LOCKASSERT(c);
	/* tell the driver to update the primary buffer if non-dma */
	chn_trigger(c, PCMTRIG_EMLDMARD);
	/* update pointers in primary buffer */
	chn_dmaupdate(c);
	/* ...and feed from primary to secondary */
	chn_rdfeed(c);
}