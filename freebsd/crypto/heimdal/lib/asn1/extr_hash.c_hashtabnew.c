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
struct TYPE_3__ {int (* cmp ) (void*,void*) ;unsigned int (* hash ) (void*) ;int sz; int /*<<< orphan*/ ** tab; } ;
typedef  TYPE_1__ Hashtab ;
typedef  int /*<<< orphan*/  Hashentry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ malloc (int) ; 

Hashtab *
hashtabnew(int sz,
	   int (*cmp) (void *, void *),
	   unsigned (*hash) (void *))
{
    Hashtab *htab;
    int i;

    assert(sz > 0);

    htab = (Hashtab *) malloc(sizeof(Hashtab) + (sz - 1) * sizeof(Hashentry *));
    if (htab == NULL)
	return NULL;

    for (i = 0; i < sz; ++i)
	htab->tab[i] = NULL;

    htab->cmp = cmp;
    htab->hash = hash;
    htab->sz = sz;
    return htab;
}