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
struct buff_file {int /*<<< orphan*/  fd; int /*<<< orphan*/  timestamp; scalar_t__ after_crc32; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int passes ; 
 struct buff_file* temp_file ; 
 int /*<<< orphan*/  tmp_adjust_global_id (struct buff_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmp_flush_out (struct buff_file*) ; 
 int /*<<< orphan*/  tmp_write_crc32 (struct buff_file*,int /*<<< orphan*/ ) ; 

int tmp_flush_all (void) {
  int i;
  for (i = 0; i < passes; i++) {
    struct buff_file *T = &temp_file[i];
    tmp_adjust_global_id (T, 0);
    if (T->after_crc32) {
      tmp_write_crc32 (T, T->timestamp);
    }
    tmp_flush_out (T);
    assert (lseek (T->fd, 0, SEEK_SET) == 0);
  }
  return passes;
}