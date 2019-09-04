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
struct TYPE_9__ {long long id; } ;
struct TYPE_7__ {TYPE_1__* targ; } ;
struct TYPE_8__ {TYPE_2__ targ; } ;
struct relative {int type; struct relative* next; TYPE_4__ node; TYPE_3__ conn; } ;
struct connection {int dummy; } ;
struct TYPE_10__ {struct relative* next; } ;
struct TYPE_6__ {struct connection* first_conn; } ;

/* Variables and functions */
 TYPE_5__ RELATIVES ; 

long long get_id_by_connection (struct connection *c) {
  struct relative *cur = RELATIVES.next;
  while (cur->type != -1) {
    if (cur->type == 0 && cur->conn.targ.targ->first_conn == c) {
      return cur->node.id;
    }
    cur = cur->next;
  }
  return 0;
}