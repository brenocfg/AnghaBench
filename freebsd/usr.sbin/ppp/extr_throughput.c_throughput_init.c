#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * fn; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_6__ {long long* SampleOctets; scalar_t__ OctetsPerSecond; } ;
struct TYPE_5__ {long long* SampleOctets; scalar_t__ OctetsPerSecond; } ;
struct pppThroughput {int SamplePeriod; TYPE_3__ callback; scalar_t__ rolling; scalar_t__ downtime; scalar_t__ uptime; TYPE_4__ Timer; int /*<<< orphan*/  BestOctetsPerSecondTime; scalar_t__ nSample; scalar_t__ BestOctetsPerSecond; TYPE_2__ out; TYPE_1__ in; scalar_t__ PacketsOut; scalar_t__ PacketsIn; scalar_t__ OctetsOut; scalar_t__ OctetsIn; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,char,int) ; 
 int /*<<< orphan*/  throughput_stop (struct pppThroughput*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
throughput_init(struct pppThroughput *t, int period)
{
  t->OctetsIn = t->OctetsOut = t->PacketsIn = t->PacketsOut = 0;
  t->SamplePeriod = period;
  t->in.SampleOctets = (long long *)
    calloc(period, sizeof *t->in.SampleOctets);
  t->in.OctetsPerSecond = 0;
  t->out.SampleOctets = (long long *)
    calloc(period, sizeof *t->out.SampleOctets);
  t->out.OctetsPerSecond = 0;
  t->BestOctetsPerSecond = 0;
  t->nSample = 0;
  time(&t->BestOctetsPerSecondTime);
  memset(&t->Timer, '\0', sizeof t->Timer);
  t->Timer.name = "throughput";
  t->uptime = 0;
  t->downtime = 0;
  t->rolling = 0;
  t->callback.data = NULL;
  t->callback.fn = NULL;
  throughput_stop(t);
}