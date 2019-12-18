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
struct name_tree_node {scalar_t__ dclass; int /*<<< orphan*/  labs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int dname_lab_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int name_tree_compare(const void* k1, const void* k2)
{
        struct name_tree_node* x = (struct name_tree_node*)k1;
        struct name_tree_node* y = (struct name_tree_node*)k2;
        int m;
        if(x->dclass != y->dclass) {
                if(x->dclass < y->dclass)
                        return -1;
                return 1;
        }
        return dname_lab_cmp(x->name, x->labs, y->name, y->labs, &m);
}