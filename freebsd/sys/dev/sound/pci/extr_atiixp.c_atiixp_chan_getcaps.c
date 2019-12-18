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
struct pcmchan_caps {int dummy; } ;
struct atiixp_chinfo {scalar_t__ caps_32bit; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 struct pcmchan_caps atiixp_caps ; 
 struct pcmchan_caps atiixp_caps_32bit ; 

__attribute__((used)) static struct pcmchan_caps *
atiixp_chan_getcaps(kobj_t obj, void *data)
{
	struct atiixp_chinfo *ch = data;

	if (ch->caps_32bit)
		return (&atiixp_caps_32bit);
	return (&atiixp_caps);
}