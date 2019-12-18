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
struct TYPE_4__ {int /*<<< orphan*/ * SampleOctets; } ;
struct TYPE_3__ {int /*<<< orphan*/ * SampleOctets; } ;
struct pppThroughput {TYPE_2__ out; TYPE_1__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throughput_stop (struct pppThroughput*) ; 

void
throughput_destroy(struct pppThroughput *t)
{
  if (t && t->in.SampleOctets) {
    throughput_stop(t);
    free(t->in.SampleOctets);
    free(t->out.SampleOctets);
    t->in.SampleOctets = NULL;
    t->out.SampleOctets = NULL;
  }
}