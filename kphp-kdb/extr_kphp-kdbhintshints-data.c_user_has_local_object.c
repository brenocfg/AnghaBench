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
struct TYPE_3__ {int /*<<< orphan*/  object_chg; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 scalar_t__ chg_has (int /*<<< orphan*/ ,int) ; 

inline int user_has_local_object (user *u, int local_id) {
  if (!local_id) {
    return 0;
  }

#ifdef HINTS
  if (user_get_object_name (u, local_id) != NULL) {
#else
  if (chg_has (u->object_chg, local_id) >= 0) {
#endif
    return local_id;
  }

  return 0;
}