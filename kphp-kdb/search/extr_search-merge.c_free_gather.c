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
struct gather_data {int magic; TYPE_2__* prev; TYPE_1__* next; } ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {TYPE_2__* prev; } ;

/* Variables and functions */
 int GD_MAGIC ; 
 int GD_MAGIC_MASK ; 
 scalar_t__ active_gathers ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void free_gather (struct gather_data *G) {
  if (!G) {
    return;
  }
  assert ((G->magic & GD_MAGIC_MASK) == GD_MAGIC);
  G->magic = 0;
  assert (active_gathers > 0);
  G->prev->next = G->next;
  G->next->prev = G->prev;
  active_gathers--;
}