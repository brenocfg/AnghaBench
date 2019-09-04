#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kfs_file_info {int flags; long long file_size; } ;
struct TYPE_3__ {long long orig_file_size; } ;
typedef  TYPE_1__ kfs_binlog_zip_header_t ;

/* Variables and functions */
 TYPE_1__* load_binlog_zip_header (struct kfs_file_info*) ; 

__attribute__((used)) static long long get_orig_file_size (struct kfs_file_info *FI) {
  if (FI->flags & 16) {
    kfs_binlog_zip_header_t *H = load_binlog_zip_header (FI);
    if (!H) {
      return -1;
    }
    return H->orig_file_size;
  }
  return FI->file_size;
}