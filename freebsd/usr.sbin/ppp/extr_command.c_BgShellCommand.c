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
struct cmdargs {scalar_t__ argc; scalar_t__ argn; } ;

/* Variables and functions */
 int ShellCommand (struct cmdargs const*,int) ; 

__attribute__((used)) static int
BgShellCommand(struct cmdargs const *arg)
{
  if (arg->argc == arg->argn)
    return -1;
  return ShellCommand(arg, 1);
}