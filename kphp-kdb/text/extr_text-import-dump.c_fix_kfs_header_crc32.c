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
struct kfs_file_header {int /*<<< orphan*/  header_crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_crc32 (struct kfs_file_header*,int) ; 

void fix_kfs_header_crc32 (struct kfs_file_header *H) {
  H->header_crc32 = compute_crc32 (H, 4092);
}