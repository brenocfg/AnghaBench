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

/* Variables and functions */
 int split_modulo ; 
 int split_rem ; 

__attribute__((used)) static inline int fits (int user_id) {
  if (user_id < 0) {
    user_id = -user_id;
  }
  return (user_id % split_modulo == split_rem);
}