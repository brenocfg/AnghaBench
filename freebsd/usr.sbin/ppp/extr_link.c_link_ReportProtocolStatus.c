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
struct prompt {int dummy; } ;
struct link {int /*<<< orphan*/ * proto_out; int /*<<< orphan*/ * proto_in; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NPROTOSTAT ; 
 TYPE_1__* ProtocolStat ; 
 int /*<<< orphan*/  prompt_Printf (struct prompt*,char*,...) ; 

void
link_ReportProtocolStatus(struct link *l, struct prompt *prompt)
{
  int i;

  prompt_Printf(prompt, "    Protocol     in        out      "
                "Protocol      in       out\n");
  for (i = 0; i < NPROTOSTAT; i++) {
    prompt_Printf(prompt, "   %-9s: %8lu, %8lu",
	    ProtocolStat[i].name, l->proto_in[i], l->proto_out[i]);
    if ((i % 2) == 0)
      prompt_Printf(prompt, "\n");
  }
  if (!(i % 2))
    prompt_Printf(prompt, "\n");
}