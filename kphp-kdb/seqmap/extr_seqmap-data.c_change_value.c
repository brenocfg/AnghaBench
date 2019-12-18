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
struct item {int value_len; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int NODE_TYPE (struct item*) ; 
 int NODE_TYPE_MINUS ; 
 int NODE_TYPE_PLUS ; 
 int NODE_TYPE_UNSURE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  change_node_type (struct item*,int) ; 
 int items_memory ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  zzfree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zzmalloc (int) ; 

void change_value (struct item *I, int value_len, int *value) {
  if (I->value_len >= 0) {
    zzfree (I->value, 4 * I->value_len);
    items_memory -= 4 * I->value_len;
  } else {
    assert (NODE_TYPE (I) == (NODE_TYPE_MINUS | NODE_TYPE_UNSURE));
    change_node_type (I, NODE_TYPE_PLUS | NODE_TYPE_UNSURE);
  }
  I->value_len = value_len;
  I->value = zzmalloc (4 * value_len);
  memcpy (I->value, value, 4 * value_len);
  items_memory += 4 * value_len;
}