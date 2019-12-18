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
struct pcmchan_caps {int dummy; } ;
struct mss_chinfo {TYPE_1__* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;
struct TYPE_2__ {int bd_id; } ;

/* Variables and functions */
#define  MD_GUSMAX 130 
#define  MD_GUSPNP 129 
#define  MD_OPTI931 128 
 struct pcmchan_caps guspnp_caps ; 
 struct pcmchan_caps mss_caps ; 
 struct pcmchan_caps opti931_caps ; 

__attribute__((used)) static struct pcmchan_caps *
msschan_getcaps(kobj_t obj, void *data)
{
	struct mss_chinfo *ch = data;

	switch(ch->parent->bd_id) {
	case MD_OPTI931:
		return &opti931_caps;
		break;

	case MD_GUSPNP:
	case MD_GUSMAX:
		return &guspnp_caps;
		break;

	default:
		return &mss_caps;
		break;
	}
}