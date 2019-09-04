#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* iseq; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  scalar_t__ mrb_code ;
typedef  int /*<<< orphan*/  mrb_aspec ;

/* Variables and functions */
 int MRB_ASPEC_OPT (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_POST (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_REQ (int /*<<< orphan*/ ) ; 
 int MRB_ASPEC_REST (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_ENTER ; 
 int /*<<< orphan*/  PEEK_W (scalar_t__*) ; 

__attribute__((used)) static int
irep_argc(mrb_irep *irep)
{
  mrb_code c;

  c = irep->iseq[0];
  if (c == OP_ENTER) {
    mrb_aspec ax = PEEK_W(irep->iseq+1);
    /* extra 1 means a slot for block */
    return MRB_ASPEC_REQ(ax)+MRB_ASPEC_OPT(ax)+MRB_ASPEC_REST(ax)+MRB_ASPEC_POST(ax)+1;
  }
  return 0;
}