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
struct TYPE_3__ {char* buff; int size; int pos; } ;
typedef  TYPE_1__ stats_buffer_t ;

/* Variables and functions */

__attribute__((used)) static void sb_truncate (stats_buffer_t *sb) {
  sb->buff[sb->size - 1] = 0;
  sb->pos = sb->size - 2;
  while (sb->pos >= 0 && sb->buff[sb->pos] != '\n') {
    sb->buff[sb->pos--] = 0;
  }
  sb->pos++;
}