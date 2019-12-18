#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ min_in; } ;
struct mp {TYPE_1__ seq; } ;
struct TYPE_4__ {scalar_t__ seq; } ;
struct datalink {TYPE_2__ mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_Assemble (struct mp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
mp_LinkLost(struct mp *mp, struct datalink *dl)
{
  if (mp->seq.min_in == dl->mp.seq)
    /* We've lost the link that's holding everything up ! */
    mp_Assemble(mp, NULL, NULL);
}