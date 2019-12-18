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
typedef  long long value_t ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 scalar_t__ do_add_list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,long long,int const*) ; 
 long long do_change_entry_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,int) ; 
 scalar_t__ entry_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 

long long do_add_incr_value (list_id_t list_id, object_id_t object_id, int flags, value_t value, const int *extra) {
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -1LL << 63;
  }
  if (entry_exists (list_id, object_id)) {
    return do_change_entry_value (list_id, object_id, value, 1);
  } else {
    if (do_add_list_entry (list_id, object_id, 2, flags, value, extra) <= 0) {
      return -1LL << 63;
    } else {
      return value;
    }
  }
}