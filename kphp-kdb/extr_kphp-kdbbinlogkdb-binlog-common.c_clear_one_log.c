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
struct log_buffer {char* log_rptr; char* log_wptr; char* log_start; char* log_end; char* log_wcrypt_ptr; scalar_t__ log_start_pos; scalar_t__ log_last_endw; scalar_t__ log_endw; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct log_buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_one_log (struct log_buffer *B, char *buffer, int size) {
  if (!buffer || !size) {
    memset (B, 0, sizeof (struct log_buffer));
    return;
  }
  B->log_rptr = B->log_wptr = B->log_start = buffer + ((16 - (long) buffer) & 15);
  B->log_end = B->log_start + size;
  B->log_endw = 0;
  B->log_last_endw = 0;
  B->log_start_pos = 0;
  B->log_wcrypt_ptr = B->log_start;
}