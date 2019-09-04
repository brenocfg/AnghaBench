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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  ll ;

/* Variables and functions */
 int /*<<< orphan*/  check_qname (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_qtype (char*) ; 
 TYPE_1__* get_queue (char*,int) ; 
 int /*<<< orphan*/  update_news (TYPE_1__*) ; 

int get_queue_alias (char *s, ll *res) {
  if (!check_qname (s, get_qtype (s))) {
    return 0;
  }
  queue *q = get_queue (s, 1);
  update_news (q);
  *res = q->id;
  return 1;
}