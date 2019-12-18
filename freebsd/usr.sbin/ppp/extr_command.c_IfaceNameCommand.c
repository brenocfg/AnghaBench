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
struct cmdargs {int argn; int argc; TYPE_1__* bundle; int /*<<< orphan*/ * argv; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {TYPE_2__* iface; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  iface_Name (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_SetTun (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IfaceNameCommand(struct cmdargs const *arg)
{
  int n = arg->argn;

  if (arg->argc != n + 1)
    return -1;

  if (!iface_Name(arg->bundle->iface, arg->argv[n]))
    return 1;

  log_SetTun(arg->bundle->unit, arg->bundle->iface->name);
  return 0;
}