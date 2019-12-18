#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t tlist; size_t nlist; size_t tbuff; size_t nbuff; int /*<<< orphan*/ * buff; int /*<<< orphan*/ ** list; } ;
typedef  TYPE_1__ stringlist_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ TW_INCR ; 
 int /*<<< orphan*/  disabled_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pintr_disabled ; 
 void* xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Char *
tw_str_add(stringlist_t *sl, size_t len)
{
    Char *ptr;

    if (sl->tlist <= sl->nlist) {
	pintr_disabled++;
	sl->tlist += TW_INCR;
	sl->list = xrealloc(sl->list, sl->tlist * sizeof(Char *));
	disabled_cleanup(&pintr_disabled);
    }
    if (sl->tbuff <= sl->nbuff + len) {
	size_t i;

	ptr = sl->buff;
	pintr_disabled++;
	sl->tbuff += TW_INCR + len;
	sl->buff = xrealloc(sl->buff, sl->tbuff * sizeof(Char));
	/* Re-thread the new pointer list, if changed */
	if (ptr != NULL && ptr != sl->buff) {
	    for (i = 0; i < sl->nlist; i++)
		sl->list[i] = sl->buff + (sl->list[i] - ptr);
	}
	disabled_cleanup(&pintr_disabled);
    }
    ptr = sl->list[sl->nlist++] = &sl->buff[sl->nbuff];
    sl->nbuff += len;
    return ptr;
}