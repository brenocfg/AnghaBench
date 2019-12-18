#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** prev; TYPE_1__* next; struct TYPE_6__* ptr; } ;
struct TYPE_5__ {struct TYPE_5__** prev; } ;
typedef  int /*<<< orphan*/  Hashtab ;
typedef  TYPE_2__ Hashentry ;

/* Variables and functions */
 TYPE_2__* _search (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

int
_hashtabdel(Hashtab * htab, void *ptr, int freep)
{
    Hashentry *h;

    assert(htab && ptr);

    h = _search(htab, ptr);
    if (h) {
	if (freep)
	    free(h->ptr);
	if ((*(h->prev) = h->next))
	    h->next->prev = h->prev;
	free(h);
	return 0;
    } else
	return -1;
}