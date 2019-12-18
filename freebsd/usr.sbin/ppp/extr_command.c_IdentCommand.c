#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cmdargs {scalar_t__ argn; scalar_t__ argv; scalar_t__ argc; TYPE_5__* cx; } ;
struct TYPE_10__ {TYPE_4__* physical; } ;
struct TYPE_6__ {int /*<<< orphan*/  ident; } ;
struct TYPE_7__ {TYPE_1__ cfg; } ;
struct TYPE_8__ {TYPE_2__ lcp; } ;
struct TYPE_9__ {TYPE_3__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  Concatinate (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
IdentCommand(struct cmdargs const *arg)
{
  Concatinate(arg->cx->physical->link.lcp.cfg.ident,
              sizeof arg->cx->physical->link.lcp.cfg.ident,
              arg->argc - arg->argn, arg->argv + arg->argn);
  return 0;
}