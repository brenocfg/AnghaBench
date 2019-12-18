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
struct lev_hints_del_object_text {long long object_id; } ;

/* Variables and functions */
 scalar_t__ LEV_HINTS_DEL_OBJECT_TEXT ; 
 struct lev_hints_del_object_text* alloc_log_event (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_object_id (long long) ; 
 int /*<<< orphan*/  check_type (int) ; 
 int del_object_text (struct lev_hints_del_object_text*) ; 

int do_del_object_text (int object_type, long long object_id) {
  if (!check_type (object_type) || !check_object_id (object_id)) {
    return 0;
  }

  struct lev_hints_del_object_text *E =
    alloc_log_event (LEV_HINTS_DEL_OBJECT_TEXT + object_type, sizeof (struct lev_hints_del_object_text), 0);

  E->object_id = object_id;

  return del_object_text (E);
}