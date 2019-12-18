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
struct prompt {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  OctetsPerSecond; } ;
struct TYPE_3__ {int /*<<< orphan*/  OctetsPerSecond; } ;
struct pppThroughput {int OctetsIn; int OctetsOut; int SamplePeriod; scalar_t__ BestOctetsPerSecondTime; int /*<<< orphan*/  BestOctetsPerSecond; TYPE_2__ out; TYPE_1__ in; scalar_t__ downtime; scalar_t__ rolling; int /*<<< orphan*/  PacketsOut; int /*<<< orphan*/  PacketsIn; } ;

/* Variables and functions */
 int ctime (scalar_t__*) ; 
 int /*<<< orphan*/  prompt_Printf (struct prompt*,char*,...) ; 
 int throughput_uptime (struct pppThroughput*) ; 

void
throughput_disp(struct pppThroughput *t, struct prompt *prompt)
{
  int secs_up, divisor;

  secs_up = throughput_uptime(t);
  prompt_Printf(prompt, "Connect time: %d:%02d:%02d", secs_up / 3600,
                (secs_up / 60) % 60, secs_up % 60);
  if (t->downtime)
    prompt_Printf(prompt, " - down at %s", ctime(&t->downtime));
  else
    prompt_Printf(prompt, "\n");

  divisor = secs_up ? secs_up : 1;
  prompt_Printf(prompt, "%llu octets in, %llu octets out\n",
                t->OctetsIn, t->OctetsOut);
  prompt_Printf(prompt, "%llu packets in, %llu packets out\n",
                t->PacketsIn, t->PacketsOut);
  if (t->rolling) {
    prompt_Printf(prompt, "  overall   %6llu bytes/sec\n",
                  (t->OctetsIn + t->OctetsOut) / divisor);
    prompt_Printf(prompt, "  %s %6llu bytes/sec in, %6llu bytes/sec out "
                  "(over the last %d secs)\n",
                  t->downtime ? "average  " : "currently",
                  t->in.OctetsPerSecond, t->out.OctetsPerSecond,
                  secs_up > t->SamplePeriod ? t->SamplePeriod : secs_up);
    prompt_Printf(prompt, "  peak      %6llu bytes/sec on %s",
                  t->BestOctetsPerSecond, ctime(&t->BestOctetsPerSecondTime));
  } else
    prompt_Printf(prompt, "Overall %llu bytes/sec\n",
                  (t->OctetsIn + t->OctetsOut) / divisor);
}