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
struct sb_info {scalar_t__ prio; scalar_t__ prio16; } ;
struct sb_chinfo {scalar_t__ dir; struct sb_info* parent; } ;
struct pcmchan_caps {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 struct pcmchan_caps sb16_caps16 ; 
 struct pcmchan_caps sb16_caps8 ; 
 struct pcmchan_caps sb16x_caps ; 

__attribute__((used)) static struct pcmchan_caps *
sb16chan_getcaps(kobj_t obj, void *data)
{
	struct sb_chinfo *ch = data;
	struct sb_info *sb = ch->parent;

	if ((sb->prio == 0) || (sb->prio == ch->dir))
		return &sb16x_caps;
	else
		return sb->prio16? &sb16_caps8 : &sb16_caps16;
}