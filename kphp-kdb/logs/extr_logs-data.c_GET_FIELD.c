#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t type; int shift; } ;
typedef  TYPE_1__ field_desc ;
struct TYPE_6__ {int sn; int* data; int /*<<< orphan*/ * std_val; } ;
typedef  TYPE_2__ event ;

/* Variables and functions */
 size_t FN ; 
 int /*<<< orphan*/  default_long ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_default ; 

inline char *GET_FIELD (event *e, field_desc *f) {
  if (f->type < 0) {
    return (char *)&e->std_val[f->type + FN];
  }

  if (unlikely(use_default)) {
    if (f->shift >= e->sn || e->data[f->shift] == -1) {
      return (char *)&default_long;
    }
  }

//  assert (f->shift < e->sn);
//    assert (e->data[f->shift] != -1);
  return &e->data[e->sn + (int)(unsigned char)e->data[f->shift]];
}