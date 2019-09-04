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
struct kfs_file_info {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 long long get_orig_file_size (struct kfs_file_info*) ; 
 int kfs_bz_compute_header_size (long long) ; 

__attribute__((used)) static int get_bz_header_size (struct kfs_file_info *FI) {
  assert (FI->flags & 16);
  long long orig_file_size = get_orig_file_size (FI);
  return kfs_bz_compute_header_size (orig_file_size);
}