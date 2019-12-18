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
struct TYPE_4__ {int user_id; scalar_t__ state; scalar_t__ lru; } ;
typedef  TYPE_1__ loaded_user_t ;

/* Variables and functions */
 TYPE_1__* LoadedUsers ; 
 scalar_t__ loaded_users_lru ; 
 int loaded_users_max ; 

loaded_user_t *find_preloaded_user (int user_id) {
  int i;
  for (i = 0; i < loaded_users_max; i++) {
    if (LoadedUsers[i].user_id == user_id && LoadedUsers[i].state > 0) {
      LoadedUsers[i].lru = ++loaded_users_lru;
      return &LoadedUsers[i];
    }
  }
  return 0;
}