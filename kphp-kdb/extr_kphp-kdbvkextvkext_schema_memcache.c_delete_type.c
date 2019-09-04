#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tl_type {int constructors_num; int extra; struct tl_type* constructors; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PFREE (int) ; 
 int /*<<< orphan*/  delete_combinator (struct tl_type) ; 
 int strlen (scalar_t__) ; 
 int /*<<< orphan*/  tl_types ; 
 int /*<<< orphan*/  zzfree (struct tl_type*,int) ; 
 int /*<<< orphan*/  zzstrfree (scalar_t__) ; 

void delete_type (struct tl_type *t) {
  if (!t) { return; }
  if (t->id) {
    ADD_PFREE (strlen (t->id));
    zzstrfree (t->id);
  }
  if (t->constructors_num && t->constructors) {
    int i;
    for (i = 0; i < t->extra; i++) {
      delete_combinator (t->constructors[i]);
    }
    zzfree (t->constructors, t->constructors_num * sizeof (void *));
    ADD_PFREE (t->constructors_num * sizeof (void *));
  }
  tl_types --;
  zzfree (t, sizeof (*t));
  ADD_PFREE (sizeof (*t));
}