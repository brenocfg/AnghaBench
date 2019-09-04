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
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_5__ {size_t nlocals; TYPE_1__* lv; } ;
typedef  TYPE_2__ mrb_irep ;
struct TYPE_4__ {size_t r; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 char* mrb_sym2name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 

__attribute__((used)) static void
print_r(mrb_state *mrb, mrb_irep *irep, size_t n)
{
  size_t i;

  if (n == 0) return;

  for (i=0; i+1<irep->nlocals; i++) {
    if (irep->lv[i].r == n) {
      mrb_sym sym = irep->lv[i].name;
      printf(" R%d:%s", (int)n, mrb_sym2name(mrb, sym));
      break;
    }
  }
}