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
typedef  int /*<<< orphan*/  field ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ data_get_hidden_state (int /*<<< orphan*/ *,int) ; 
 int data_get_local_id_by_id (int /*<<< orphan*/ *,int) ; 
 int user_change_data_lid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

inline int user_change_data (data *d, int id, field *field_changes, int field_changes_n, int force) {
//  dbg ("user_change_data ???: id = %d, field_changes_n = %d\n", id, field_changes_n);

  assert (d != NULL);
  int lid = data_get_local_id_by_id (d, id);
  if (lid == -1) {
    return 0;
  }

  if (!force && data_get_hidden_state (d, id) != 0) {
    return 0;
  }

  return user_change_data_lid (d, lid, field_changes, field_changes_n);
}