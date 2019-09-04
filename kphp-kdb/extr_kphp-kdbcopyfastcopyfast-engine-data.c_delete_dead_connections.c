#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct relative {int type; TYPE_4__* prev; struct relative* next; } ;
struct TYPE_10__ {struct relative* next; } ;
struct TYPE_6__ {scalar_t__ generation; TYPE_3__* conn; } ;
struct TYPE_7__ {TYPE_1__ conn; } ;
struct TYPE_9__ {int type; TYPE_2__ conn; } ;
struct TYPE_8__ {scalar_t__ generation; scalar_t__ last_response_time; } ;

/* Variables and functions */
 scalar_t__ IDLE_LIMIT ; 
 TYPE_5__ RELATIVES ; 
 scalar_t__ cr_ok ; 
 int /*<<< orphan*/  delete_relative (TYPE_4__*,int) ; 
 scalar_t__ precise_now ; 
 scalar_t__ server_check_ready (TYPE_3__*) ; 

void delete_dead_connections (void) {
  struct relative *cur = RELATIVES.next;
  while (cur->type != -1) {
    cur = cur->next;
    if (cur->prev->type == 1) {
      if (cur->prev->conn.conn.conn->generation != cur->prev->conn.conn.generation ||
        server_check_ready (cur->prev->conn.conn.conn) != cr_ok || 
        cur->prev->conn.conn.conn->last_response_time + IDLE_LIMIT < precise_now) {
        delete_relative (cur->prev, 1);
      }
    }
  }
}