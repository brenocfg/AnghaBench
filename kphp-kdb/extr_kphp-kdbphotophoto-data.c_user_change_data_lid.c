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
struct TYPE_3__ {int fn; int /*<<< orphan*/ * f; int /*<<< orphan*/  tp; } ;
typedef  TYPE_1__ my_change ;
typedef  int /*<<< orphan*/  field ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ch_fields ; 
 int data_add_change (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

inline int user_change_data_lid (data *d, int lid, field *field_changes, int field_changes_n) {
//  dbg ("user_change_data_lid ???: local_id = %d, field_changes_n = %d\n", lid, field_changes_n);

  assert (d != NULL && lid >= 0);

  my_change ch;
  ch.tp = ch_fields;
  ch.f = field_changes;
  ch.fn = field_changes_n;

//  dbg ("data add change %d\n", lid);
  return data_add_change (d, &ch, lid);
}