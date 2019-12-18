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
struct TYPE_2__ {scalar_t__ scrub_flag; } ;
struct pfsync_state_peer {TYPE_1__ scrub; } ;
struct pf_state_peer {int /*<<< orphan*/ * scrub; } ;

/* Variables and functions */
 int ENOMEM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_pf_state_scrub_z ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pfsync_alloc_scrub_memory(struct pfsync_state_peer *s,
    struct pf_state_peer *d)
{
	if (s->scrub.scrub_flag && d->scrub == NULL) {
		d->scrub = uma_zalloc(V_pf_state_scrub_z, M_NOWAIT | M_ZERO);
		if (d->scrub == NULL)
			return (ENOMEM);
	}

	return (0);
}