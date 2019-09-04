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
typedef  int list_id_t ;

/* Variables and functions */
 int MAX_USERS ; 
 scalar_t__ allow_negative ; 
 int split_mod ; 
 int split_rem ; 

int conv_uid (list_id_t id) {
  if (id < 0 && allow_negative) {
    id = -id;
  }
  if (id <= 0 || id >= split_mod * MAX_USERS) {
    return -1;
  }
  return id % split_mod == split_rem ? id / split_mod : -1;
}