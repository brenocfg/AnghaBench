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
struct csa_chinfo {scalar_t__ dir; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 struct pcmchan_caps csa_playcaps ; 
 struct pcmchan_caps csa_reccaps ; 

__attribute__((used)) static struct pcmchan_caps *
csachan_getcaps(kobj_t obj, void *data)
{
	struct csa_chinfo *ch = data;
	return (ch->dir == PCMDIR_PLAY)? &csa_playcaps : &csa_reccaps;
}