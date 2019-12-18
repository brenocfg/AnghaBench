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
struct via_info {scalar_t__ dxs_src; } ;
struct via_chinfo {struct via_info* parent; } ;
struct pcmchan_caps {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 struct pcmchan_caps via_caps ; 
 struct pcmchan_caps via_vracaps ; 

__attribute__((used)) static struct pcmchan_caps *
via8233dxs_getcaps(kobj_t obj, void *data)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;

	/*
	 * Controlled by onboard registers
	 *
	 * Apparently, few boards can do DXS sample rate
	 * conversion.
	 */
	if (via->dxs_src)
		return (&via_vracaps);
	return (&via_caps);
}