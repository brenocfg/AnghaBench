#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {struct val_neg_zone* key; } ;
struct val_neg_zone {size_t len; int labs; int /*<<< orphan*/  tree; int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; TYPE_1__ node; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct val_neg_zone*) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val_neg_data_compare ; 

__attribute__((used)) static struct val_neg_zone* neg_setup_zone_node(
	uint8_t* nm, size_t nm_len, int labs, uint16_t dclass)
{
	struct val_neg_zone* zone = 
		(struct val_neg_zone*)calloc(1, sizeof(*zone));
	if(!zone) {
		return NULL;
	}
	zone->node.key = zone;
	zone->name = memdup(nm, nm_len);
	if(!zone->name) {
		free(zone);
		return NULL;
	}
	zone->len = nm_len;
	zone->labs = labs;
	zone->dclass = dclass;

	rbtree_init(&zone->tree, &val_neg_data_compare);
	return zone;
}