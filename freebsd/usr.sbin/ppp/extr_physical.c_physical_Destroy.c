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
struct TYPE_3__ {int /*<<< orphan*/  total; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct physical {TYPE_2__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct physical*) ; 
 int /*<<< orphan*/  physical_Close (struct physical*) ; 
 int /*<<< orphan*/  throughput_destroy (int /*<<< orphan*/ *) ; 

void
physical_Destroy(struct physical *p)
{
  physical_Close(p);
  throughput_destroy(&p->link.stats.total);
  free(p);
}