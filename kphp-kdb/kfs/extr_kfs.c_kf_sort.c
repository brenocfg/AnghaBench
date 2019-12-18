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
typedef  int /*<<< orphan*/  T ;

/* Variables and functions */
 int /*<<< orphan*/  qsort (struct kfs_file_info**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_cmp_file_info ; 

__attribute__((used)) static void kf_sort (struct kfs_file_info **T, int n) {
  qsort (T, n, sizeof (T[0]), qsort_cmp_file_info);
}