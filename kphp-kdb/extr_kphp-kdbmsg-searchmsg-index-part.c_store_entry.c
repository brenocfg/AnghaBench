#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; } ;
typedef  TYPE_1__ entry_t ;

/* Variables and functions */
 int TEXT_SIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* mymalloc (int) ; 

entry_t *store_entry (entry_t *E) {
  int r = sizeof(entry_t) - TEXT_SIZE + E->len + 1;
  entry_t *R = mymalloc (r);
  assert (R);
  memcpy (R, E, r);
  return R;
}