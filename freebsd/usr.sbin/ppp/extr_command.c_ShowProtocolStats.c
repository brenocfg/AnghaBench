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
struct link {int /*<<< orphan*/  name; } ;
struct cmdargs {int /*<<< orphan*/  prompt; } ;

/* Variables and functions */
 struct link* command_ChooseLink (struct cmdargs const*) ; 
 int /*<<< orphan*/  link_ReportProtocolStatus (struct link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prompt_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ShowProtocolStats(struct cmdargs const *arg)
{
  struct link *l = command_ChooseLink(arg);

  prompt_Printf(arg->prompt, "%s:\n", l->name);
  link_ReportProtocolStatus(l, arg->prompt);
  return 0;
}