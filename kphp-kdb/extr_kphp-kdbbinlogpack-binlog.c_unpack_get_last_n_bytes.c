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
struct TYPE_3__ {int write_buff_off; int size; int off; } ;
typedef  TYPE_1__ unpack_interval_t ;

/* Variables and functions */
 int KFS_BINLOG_ZIP_CHUNK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int unpack_get_last_n_bytes (unsigned long long orig_file_size, int m, int chunk_no, int chunks, int n, unpack_interval_t *R) {
  unsigned u = orig_file_size;
  u &= (KFS_BINLOG_ZIP_CHUNK_SIZE - 1);
  if (u >= n) {
    if (chunk_no == chunks - 1) {
      R->write_buff_off = m - n;
      R->size = n;
      R->off = 0;
      return 0;
    }
    return -1;
  } else {
    if (chunk_no == chunks - 1) {
      R->write_buff_off = 0;
      R->size = u;
      R->off = n - u;
      return 0;
    } else {
      assert (chunk_no == chunks - 2);
      u = n - u;
      R->write_buff_off = m - u;
      R->size = u;
      R->off = 0;
      return 0;
    }
  }
}