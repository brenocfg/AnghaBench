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
struct sc_rchinfo {int /*<<< orphan*/  adc_idx; } ;
struct pcmchan_caps {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 struct pcmchan_caps m3_reccaps ; 

__attribute__((used)) static struct pcmchan_caps *
m3_rchan_getcaps(kobj_t kobj, void *chdata)
{
	struct sc_rchinfo *ch = chdata;

        M3_DEBUG(CALL, ("m3_rchan_getcaps(adc=%d)\n", ch->adc_idx));

	return &m3_reccaps;
}