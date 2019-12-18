#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* parent; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static Con *lowest_common_ancestor(Con *a, Con *b) {
    Con *parent_a = a;
    while (parent_a) {
        Con *parent_b = b;
        while (parent_b) {
            if (parent_a == parent_b) {
                return parent_a;
            }
            parent_b = parent_b->parent;
        }
        parent_a = parent_a->parent;
    }
    assert(false);
}