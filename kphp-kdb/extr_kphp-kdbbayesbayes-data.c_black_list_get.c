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
struct TYPE_3__ {int text_len; struct TYPE_3__* next; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ black_list ;

/* Variables and functions */
 TYPE_1__* bl_head ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

int black_list_get (char *buf, int buf_len) {
  black_list *cur = bl_head;
  int cur_len = 0;
  while (cur->next != NULL && cur->next->text_len + cur_len + 1 < buf_len) {
    memcpy (buf + cur_len, cur->next->text, cur->next->text_len);
    cur_len += cur->next->text_len;
    buf[cur_len++] = '\t';
    cur = cur->next;
  }
  if (cur_len == 0) {
    cur_len = 1;
  }
  buf[cur_len - 1] = 0;

  if (cur->next != NULL) {
    return -1;
  }

  return cur_len - 1;
}