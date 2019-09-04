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
 void* RBuff ; 
 void* RBuffEnd ; 
 int /*<<< orphan*/  assert (int) ; 
 long long idx_bytes ; 
 long idx_metafile_pos ; 
 void* idx_ptr_crc ; 
 long long idx_read_pos ; 
 void* idx_rptr ; 
 void* idx_wptr ; 
 int read_crc32_acc ; 

void idx_fake_readpos (long long pos) {
  long len = RBuffEnd - RBuff;
  assert (len > 0 && pos + len <= idx_bytes && pos >= 0);
  idx_read_pos = pos + len;
  idx_metafile_pos = len;
  read_crc32_acc = -1;
  idx_rptr = idx_ptr_crc = RBuff;
  idx_wptr = RBuffEnd;
}