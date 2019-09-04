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
struct jv_parser {scalar_t__ curr_buf; int curr_buf_length; int curr_buf_pos; } ;

/* Variables and functions */

int jv_parser_remaining(struct jv_parser* p) {
  if (p->curr_buf == 0)
    return 0;
  return (p->curr_buf_length - p->curr_buf_pos);
}