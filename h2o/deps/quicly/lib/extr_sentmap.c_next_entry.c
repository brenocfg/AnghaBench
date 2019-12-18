#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ count; TYPE_3__* p; TYPE_1__** ref; } ;
typedef  TYPE_2__ quicly_sentmap_iter_t ;
struct TYPE_7__ {int /*<<< orphan*/ * acked; } ;
typedef  TYPE_3__ quicly_sent_t ;
struct TYPE_5__ {scalar_t__ num_entries; TYPE_3__* entries; struct TYPE_5__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  quicly_sentmap__end_iter ; 

__attribute__((used)) static void next_entry(quicly_sentmap_iter_t *iter)
{
    if (--iter->count != 0) {
        ++iter->p;
    } else if (*(iter->ref = &(*iter->ref)->next) == NULL) {
        iter->p = (quicly_sent_t *)&quicly_sentmap__end_iter;
        iter->count = 0;
        return;
    } else {
        assert((*iter->ref)->num_entries != 0);
        iter->count = (*iter->ref)->num_entries;
        iter->p = (*iter->ref)->entries;
    }
    while (iter->p->acked == NULL)
        ++iter->p;
}