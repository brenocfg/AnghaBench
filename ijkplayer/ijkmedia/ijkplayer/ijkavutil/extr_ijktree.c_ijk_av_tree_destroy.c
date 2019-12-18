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
struct TYPE_4__ {struct TYPE_4__** child; } ;
typedef  TYPE_1__ IjkAVTreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void ijk_av_tree_destroy(IjkAVTreeNode *t)
{
    if (t) {
        ijk_av_tree_destroy(t->child[0]);
        ijk_av_tree_destroy(t->child[1]);
        free(t);
    }
}