#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_4__ {char* buff; int size; int pos; } ;
typedef  TYPE_1__ stats_buffer_t ;

/* Variables and functions */
 int prepare_stats (struct connection*,char*,int) ; 
 int /*<<< orphan*/  sb_truncate (TYPE_1__*) ; 

void sb_prepare (stats_buffer_t *sb, struct connection *c, char *buff, int size) {
  sb->buff = buff;
  sb->size = size;
  sb->pos = prepare_stats (c, buff, size);
  if ((sb->pos == size - 1 && sb->buff[sb->pos]) || sb->pos >= size) {
    sb_truncate (sb);
  }
}