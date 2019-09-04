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
struct TYPE_4__ {struct TYPE_4__* right; struct TYPE_4__* parent; } ;
typedef  TYPE_1__ node_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  add_bit (int,int /*<<< orphan*/ *) ; 
 int bloc ; 

__attribute__((used)) static void send(node_t *node, node_t *child, byte *fout, int maxoffset) {
	if (node->parent) {
		send(node->parent, node, fout, maxoffset);
	}
	if (child) {
		if (bloc >= maxoffset) {
			bloc = maxoffset + 1;
			return;
		}
		if (node->right == child) {
			add_bit(1, fout);
		} else {
			add_bit(0, fout);
		}
	}
}