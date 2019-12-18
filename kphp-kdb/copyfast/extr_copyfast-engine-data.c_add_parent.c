#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct node {int /*<<< orphan*/  host; } ;
struct TYPE_5__ {int /*<<< orphan*/  generation; struct connection* conn; } ;
struct TYPE_6__ {TYPE_1__ conn; } ;
struct relative {int type; size_t link_color; struct node node; TYPE_2__ conn; struct relative* prev; struct relative* next; } ;
struct connection {int /*<<< orphan*/  generation; } ;
struct TYPE_7__ {int /*<<< orphan*/  total_parents; int /*<<< orphan*/ * total_links_color; } ;
struct TYPE_8__ {TYPE_3__ structured; } ;

/* Variables and functions */
 struct relative RELATIVES ; 
 TYPE_4__* STATS ; 
 int /*<<< orphan*/  host ; 
 size_t link_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct relative* zmalloc (int) ; 

void add_parent (struct node child, struct connection *c) {
  struct relative *cur = zmalloc (sizeof (struct relative));
  cur->next = RELATIVES.next;
  cur->prev = &RELATIVES;
  cur->prev->next = cur;
  cur->next->prev = cur;
  cur->node = child;
  cur->type = 1;
  cur->conn.conn.conn = c;
  cur->conn.conn.generation = c->generation;
  cur->link_color = link_color (cur->node.host, host);
  STATS->structured.total_links_color[cur->link_color]++;
  STATS->structured.total_parents ++;
}