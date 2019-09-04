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
struct TYPE_5__ {int shift; } ;
typedef  TYPE_1__ field_desc ;
struct TYPE_6__ {int sn; char* data; } ;
typedef  TYPE_2__ event ;

/* Variables and functions */
 char* default_string ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_default ; 

inline char *GET_STRING (event *e, field_desc *f) {
  if (unlikely(use_default)) {
    if (f->shift >= e->sn || *(short *)&e->data[f->shift] == -1) {
      return default_string;
    }
  }

//  assert (f->shift < e->sn);
//    assert ((int)*(short *)&e->data[f->shift] >= 0);
  return &e->data[e->sn + (int)*(short *)&e->data[f->shift]];
}