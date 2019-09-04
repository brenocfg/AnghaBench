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
struct kfs_file_info {int dummy; } ;

/* Variables and functions */
 int cmp_file_info (struct kfs_file_info const*,struct kfs_file_info const*) ; 

__attribute__((used)) static int qsort_cmp_file_info (const void *x, const void *y) {
  return cmp_file_info (*(const struct kfs_file_info **) x, *(const struct kfs_file_info **) y);
}