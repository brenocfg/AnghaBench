#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* loop; } ;
typedef  TYPE_2__ codegen_scope ;
struct TYPE_6__ {struct TYPE_6__* prev; int /*<<< orphan*/  pc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_LOADNIL ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  dispatch_linked (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push () ; 

__attribute__((used)) static void
loop_pop(codegen_scope *s, int val)
{
  if (val) {
    genop_1(s, OP_LOADNIL, cursp());
  }
  dispatch_linked(s, s->loop->pc3);
  s->loop = s->loop->prev;
  if (val) push();
}