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
 int /*<<< orphan*/  RBuff ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 long long idx_bytes ; 
 int /*<<< orphan*/  idx_fd ; 
 scalar_t__ idx_metafile_pos ; 
 int /*<<< orphan*/  idx_ptr_crc ; 
 long long idx_read_pos ; 
 int /*<<< orphan*/  idx_rptr ; 
 int /*<<< orphan*/  idx_wptr ; 
 long long lseek (int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ) ; 
 int read_crc32_acc ; 

void idx_set_readpos (long long pos) {
  assert (pos <= idx_bytes && pos >= 0);
  assert (lseek (idx_fd, pos, SEEK_SET) == pos);
  idx_read_pos = pos;
  idx_metafile_pos = 0;
  read_crc32_acc = -1;
  idx_rptr = idx_wptr = idx_ptr_crc = RBuff;
}