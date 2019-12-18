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
struct kfs_file_info {scalar_t__ min_log_pos; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cmp_file_info (const struct kfs_file_info *FI, const struct kfs_file_info *FJ) {
  if (FI->min_log_pos < FJ->min_log_pos) {
    return -1;
  } else if (FI->min_log_pos > FJ->min_log_pos) {
    return 1;
  } else {
    return strcmp (FI->filename, FJ->filename);
  }
}