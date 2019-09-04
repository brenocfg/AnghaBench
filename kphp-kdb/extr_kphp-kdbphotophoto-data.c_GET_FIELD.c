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
struct TYPE_5__ {int shift; scalar_t__ type; } ;
typedef  TYPE_1__ field_desc ;
struct TYPE_6__ {int sn; char* data; } ;
typedef  TYPE_2__ event ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ t_raw ; 
 scalar_t__ t_string ; 

inline char *GET_FIELD (event *e, field_desc *f) {
  if (likely (f->shift < e->sn)) {
    if (f->type == t_string || f->type == t_raw) {
      assert ((int)*(short *)&e->data[f->shift] >= 0);
      return &e->data[e->sn + (int)*(short *)&e->data[f->shift]];
    } else {
      assert (e->data[f->shift] != -1);
      return &e->data[e->sn + (int)(unsigned char)e->data[f->shift]];
    }
  }
  return NULL;
}