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
struct TYPE_4__ {int index; int /*<<< orphan*/ * nextEntry; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * ht; } ;
typedef  TYPE_1__ dictIterator ;
typedef  int /*<<< orphan*/  dict ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static dictIterator *dictGetIterator(dict *ht) {
    dictIterator *iter = malloc(sizeof(*iter));

    iter->ht = ht;
    iter->index = -1;
    iter->entry = NULL;
    iter->nextEntry = NULL;
    return iter;
}