#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sc_pcminfo {int dummy; } ;
struct sc_chinfo {scalar_t__ dir; struct sc_pcminfo* parent; } ;
struct pcmchan_caps {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct pcmchan_caps hdspe_pcaps ; 
 struct pcmchan_caps hdspe_rcaps ; 
 TYPE_1__* scp ; 

__attribute__((used)) static struct pcmchan_caps *
hdspechan_getcaps(kobj_t obj, void *data)
{
	struct sc_chinfo *ch;

	ch = data;

#if 0
	struct sc_pcminfo *scl = ch->parent;
	device_printf(scp->dev, "hdspechan_getcaps()\n");
#endif

	return ((ch->dir == PCMDIR_PLAY) ?
	    &hdspe_pcaps : &hdspe_rcaps);
}