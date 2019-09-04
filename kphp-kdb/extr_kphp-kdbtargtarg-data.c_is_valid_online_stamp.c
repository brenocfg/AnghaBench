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
 int OLIST_COUNT ; 
 int ocur_now ; 

__attribute__((used)) static inline int is_valid_online_stamp (int ts) {
  return ocur_now && ts > ocur_now - OLIST_COUNT;
}