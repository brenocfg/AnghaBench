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
typedef  int uint8_t ;
struct TYPE_2__ {int start_pos; int* ch; } ;
struct tr_pattern {scalar_t__ type; int n; struct tr_pattern* next; TYPE_1__ val; scalar_t__ flag_reverse; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ TR_IN_ORDER ; 
 scalar_t__ TR_RANGE ; 
 scalar_t__ TR_UNINITIALIZED ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  tr_bitmap_set (int*,char const) ; 

__attribute__((used)) static void
tr_compile_pattern(const struct tr_pattern *pat, mrb_value pstr, uint8_t bitmap[32])
{
  const char *pattern = RSTRING_PTR(pstr);
  mrb_int flag_reverse = pat ? pat->flag_reverse : 0;
  int i;

  for (i=0; i<32; i++) {
    bitmap[i] = 0;
  }
  while (pat != NULL) {
    if (pat->type == TR_IN_ORDER) {
      for (i = 0; i < pat->n; i++) {
        tr_bitmap_set(bitmap, pattern[pat->val.start_pos + i]);
      }
    }
    else if (pat->type == TR_RANGE) {
      for (i = pat->val.ch[0]; i < pat->val.ch[1]; i++) {
        tr_bitmap_set(bitmap, i);
      }
    }
    else {
      mrb_assert(pat->type == TR_UNINITIALIZED);
    }
    pat = pat->next;
  }

  if (flag_reverse) {
    for (i=0; i<32; i++) {
      bitmap[i] ^= 0xff;
    }
  }
}