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
struct TYPE_3__ {char* buff; int size; scalar_t__ pos; } ;
typedef  TYPE_1__ cache_buffer_t ;

/* Variables and functions */

void cache_bclear (cache_buffer_t *b, char *buff, int size) {
  b->buff = buff;
  b->size = size;
  b->pos = 0;
}