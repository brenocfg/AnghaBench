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
typedef  scalar_t__ time_t ;
struct TYPE_4__ {scalar_t__* SampleOctets; } ;
struct TYPE_3__ {scalar_t__* SampleOctets; } ;
struct pppThroughput {scalar_t__ downtime; scalar_t__ uptime; int SamplePeriod; scalar_t__ nSample; TYPE_2__ out; TYPE_1__ in; } ;

/* Variables and functions */
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
throughput_uptime(struct pppThroughput *t)
{
  time_t downat;

  downat = t->downtime ? t->downtime : time(NULL);
  if (t->uptime && downat < t->uptime) {
    /* Euch !  The clock's gone back ! */
    int i;

    for (i = 0; i < t->SamplePeriod; i++)
      t->in.SampleOctets[i] = t->out.SampleOctets[i] = 0;
    t->nSample = 0;
    t->uptime = downat;
  }
  return t->uptime ? downat - t->uptime : 0;
}