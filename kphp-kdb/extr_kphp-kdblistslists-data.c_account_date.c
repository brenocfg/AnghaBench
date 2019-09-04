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
 int /*<<< orphan*/ * R ; 
 int account_date_buckets ; 
 int account_date_step ; 
 int account_max_date ; 
 int account_min_date ; 

__attribute__((used)) static inline int account_date (int date) {
  if (date < account_min_date) {
    R[0]++;
  } else if (date < account_max_date) {
    R[(date - account_min_date) / account_date_step + 1]++;
  } else {
    R[account_date_buckets + 1]++;
  }
  return 1;
}