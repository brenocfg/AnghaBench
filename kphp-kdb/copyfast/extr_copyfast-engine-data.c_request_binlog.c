#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct relative {int type; scalar_t__ binlog_position; scalar_t__ timestamp; size_t link_color; TYPE_1__ node; struct relative* next; } ;
struct connection {int dummy; } ;
struct TYPE_4__ {struct relative* next; } ;

/* Variables and functions */
 scalar_t__ BINLOG_POSITION ; 
 scalar_t__ LAST_BINLOG_REQUEST_TIME ; 
 TYPE_2__ RELATIVES ; 
 scalar_t__ REQUEST_BINLOG_DELAY ; 
 scalar_t__* REQUEST_DELAY ; 
 int /*<<< orphan*/  assert (int) ; 
 struct connection* get_relative_connection (struct relative*) ; 
 int lrand48 () ; 
 scalar_t__ precise_now ; 
 int /*<<< orphan*/  rpc_send_binlog_request (struct connection*,int /*<<< orphan*/ ,int) ; 

void request_binlog (void) {
  if (LAST_BINLOG_REQUEST_TIME + REQUEST_BINLOG_DELAY > precise_now) {
    return;
  }
  struct relative *cur = RELATIVES.next;
  struct relative *best = 0;
  int best_color = 0;
  int ncolor = 0;
  while (cur->type != -1) {
    if (cur->binlog_position > BINLOG_POSITION && precise_now >= cur->timestamp + REQUEST_DELAY[cur->link_color]) {
      if (cur->link_color == best_color){
        ncolor ++;
        if (lrand48 () % (ncolor) == 0) {
            best = cur;
        }
      } else if (cur->link_color > best_color) {
        ncolor = 1;
        best_color = cur->link_color;
        best = cur;
      }
    }
    cur = cur->next;
  }
  if (best) {
    assert (best_color >= 0 && best_color <= 2);
    struct connection *c = get_relative_connection (best);
    if (c) {
      rpc_send_binlog_request (c, best->node.id, -1);
      LAST_BINLOG_REQUEST_TIME = precise_now;
    }
  }
}