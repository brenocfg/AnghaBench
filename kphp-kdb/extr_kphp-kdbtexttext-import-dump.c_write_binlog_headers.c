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
struct TYPE_3__ {int /*<<< orphan*/  raw_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_crc32; scalar_t__ finished; int /*<<< orphan*/  header_seq_num; int /*<<< orphan*/  modified; } ;

/* Variables and functions */
 TYPE_1__* KHDR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int binlog_headers ; 
 int /*<<< orphan*/  fix_kfs_header_crc32 (TYPE_1__*) ; 
 int /*<<< orphan*/  kfs_Hdr ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  targ_fd ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tot_crc32 ; 
 scalar_t__ wr_bytes ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void write_binlog_headers (void) {
  int i;

  if (!KHDR) {
    return;
  }
 
  KHDR->modified = time (0);
  ++KHDR->header_seq_num;
  KHDR->finished = 0;
  KHDR->data_crc32 = ~tot_crc32;
  KHDR->data_size += wr_bytes;
  KHDR->raw_size += wr_bytes;

  fix_kfs_header_crc32 (KHDR);

  assert (lseek (targ_fd, 0, SEEK_SET) == 0);
  for (i = 0; i < binlog_headers; i++) {
    assert (write (targ_fd, kfs_Hdr, 4096) == 4096);
  }
}