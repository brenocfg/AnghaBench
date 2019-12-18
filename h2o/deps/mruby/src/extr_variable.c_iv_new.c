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
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_3__ {scalar_t__ last_len; int /*<<< orphan*/ * rootseg; scalar_t__ size; } ;
typedef  TYPE_1__ iv_tbl ;

/* Variables and functions */
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static iv_tbl*
iv_new(mrb_state *mrb)
{
  iv_tbl *t;

  t = (iv_tbl*)mrb_malloc(mrb, sizeof(iv_tbl));
  t->size = 0;
  t->rootseg =  NULL;
  t->last_len = 0;

  return t;
}