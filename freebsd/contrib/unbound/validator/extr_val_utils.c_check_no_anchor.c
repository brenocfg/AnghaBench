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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct trust_anchor* anchors_lookup (struct val_anchors*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_no_anchor(struct val_anchors* anchors, uint8_t* nm, size_t l, uint16_t c)
{
	struct trust_anchor* ta;
	if((ta=anchors_lookup(anchors, nm, l, c))) {
		lock_basic_unlock(&ta->lock);
	}
	return !ta;
}