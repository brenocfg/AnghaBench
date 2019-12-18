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
typedef  int /*<<< orphan*/  user ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_ID (int,int) ; 
 int user_get_object_local_id_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int user_get_object_local_id (user *u, int type, int object_id) {
  return user_get_object_local_id_type_id (u, TYPE_ID(type, object_id));
}