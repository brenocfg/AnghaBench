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
 int user_get_object_local_id (int /*<<< orphan*/ *,int,int) ; 
 int user_has_local_object (int /*<<< orphan*/ *,int) ; 

inline int user_has_object (user *u, int type, int id) {
  int local_id = user_get_object_local_id (u, type, id);

  return user_has_local_object (u, local_id);
}