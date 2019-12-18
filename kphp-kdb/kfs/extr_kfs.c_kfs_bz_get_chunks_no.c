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
 int KFS_BINLOG_ZIP_CHUNK_SIZE ; 
 long long KFS_BINLOG_ZIP_CHUNK_SIZE_EXP ; 

int kfs_bz_get_chunks_no (long long orig_file_size) {
  return (orig_file_size + (KFS_BINLOG_ZIP_CHUNK_SIZE - 1)) >> KFS_BINLOG_ZIP_CHUNK_SIZE_EXP;
}