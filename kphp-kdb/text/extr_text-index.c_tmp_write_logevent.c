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
struct buff_file {int after_crc32; scalar_t__ timestamp; } ;

/* Variables and functions */
 scalar_t__ is_message_event ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  tmp_adjust_global_id (struct buff_file*,int) ; 
 int /*<<< orphan*/  tmp_write_crc32 (struct buff_file*,scalar_t__) ; 
 int /*<<< orphan*/  tmp_write_lev (struct buff_file*,void const*,int) ; 
 int /*<<< orphan*/  tmp_write_ts (struct buff_file*,scalar_t__) ; 

void tmp_write_logevent (struct buff_file *T, const void *L, int size) {
  if (T->after_crc32 > 16384) {
    tmp_write_crc32 (T, now);
  } else if (now != T->timestamp && now) {
    tmp_write_ts (T, now);
  }
  if (is_message_event) {
    tmp_adjust_global_id (T, 1);
  }
  tmp_write_lev (T, L, size);
}