#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* cdr; TYPE_1__* car; } ;
typedef  TYPE_2__ node ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_4__ {int /*<<< orphan*/  car; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NODE_SPLAT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ nint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
nosplat(node *t)
{
  while (t) {
    if (nint(t->car->car) == NODE_SPLAT) return FALSE;
    t = t->cdr;
  }
  return TRUE;
}