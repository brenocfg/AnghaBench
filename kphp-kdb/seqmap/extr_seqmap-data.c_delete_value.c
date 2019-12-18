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
 int NODE_TYPE_SURE ; 
 int NODE_TYPE_UNSURE ; 
 int NODE_TYPE_ZERO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  change_node_type (struct item*,int) ; 
 int /*<<< orphan*/  free_item (struct item*) ; 
 int items_memory ; 
 int /*<<< orphan*/  zzfree (int /*<<< orphan*/ ,int) ; 

void delete_value (struct item *I) {
  if (I->value_len >= 0) {
    if (NODE_TYPE (I) == (NODE_TYPE_PLUS | NODE_TYPE_UNSURE)) {
      zzfree (I->value, 4 * I->value_len);
      items_memory -= 4 * I->value_len;
      I->value_len = -1;
      change_node_type (I, NODE_TYPE_MINUS | NODE_TYPE_UNSURE);
    } else if (NODE_TYPE (I) == (NODE_TYPE_PLUS | NODE_TYPE_SURE)) {
      free_item (I);
    } else {
      assert (NODE_TYPE (I) == (NODE_TYPE_ZERO | NODE_TYPE_SURE));
      zzfree (I->value, 4 * I->value_len);
      items_memory -= 4 * I->value_len;
      I->value_len = -1;
      change_node_type (I, NODE_TYPE_MINUS | NODE_TYPE_SURE);
    }
  }
}