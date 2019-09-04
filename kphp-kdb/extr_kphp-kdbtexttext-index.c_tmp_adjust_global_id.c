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
struct lev_generic {int a; scalar_t__ type; } ;
struct buff_file {int global_id; } ;

/* Variables and functions */
 scalar_t__ LEV_TX_INCREASE_GLOBAL_ID_LARGE ; 
 scalar_t__ LEV_TX_INCREASE_GLOBAL_ID_SMALL ; 
 int /*<<< orphan*/  assert (int) ; 
 int last_global_id ; 
 int /*<<< orphan*/  tmp_write_lev (struct buff_file*,struct lev_generic*,int) ; 

void tmp_adjust_global_id (struct buff_file *T, int is_message_event) {
  int v = last_global_id - T->global_id - is_message_event;
  assert (v >= 0);
  static struct lev_generic lgid;
  if (v > 0 && v <= 0xffff) {
    lgid.type = v + LEV_TX_INCREASE_GLOBAL_ID_SMALL;
    tmp_write_lev (T, &lgid, 4);
  } else if (v) {
    lgid.type = LEV_TX_INCREASE_GLOBAL_ID_LARGE;
    lgid.a = v;
    tmp_write_lev (T, &lgid, 8);
  }
  T->global_id = last_global_id;
}