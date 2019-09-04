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
struct TYPE_3__ {long long id; } ;
struct relative {int type; struct relative* next; TYPE_1__ node; } ;
struct TYPE_4__ {struct relative* next; } ;

/* Variables and functions */
 TYPE_2__ RELATIVES ; 

struct relative *get_relative_by_id (long long id) {
  struct relative *cur = RELATIVES.next;
  while (cur->type != -1) {
    if (cur->node.id == id) {
      return cur;
    }
    cur = cur->next;
  }
  return 0;
}