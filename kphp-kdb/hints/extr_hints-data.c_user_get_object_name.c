#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int object_old_n; int* object_indexes; char* object_data; char** object_names; } ;
typedef  TYPE_1__ user ;

/* Variables and functions */
 int MEM_FLAG ; 
 int /*<<< orphan*/  check (TYPE_1__*,int) ; 

char *user_get_object_name (user *u, int local_id) {
  check (u, local_id);

  if (local_id <= u->object_old_n) {
    if (u->object_indexes[local_id] & MEM_FLAG) {
      return *((char **)(u->object_data + (u->object_indexes[local_id] & ~MEM_FLAG)));
    } else {
      return (u->object_data + u->object_indexes[local_id]);
    }
  } else {
    return u->object_names[local_id - u->object_old_n];
  }
}