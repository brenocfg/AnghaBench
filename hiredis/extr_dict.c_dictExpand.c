#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ dictEntry ;
struct TYPE_9__ {unsigned long used; unsigned long size; unsigned long sizemask; TYPE_1__** table; int /*<<< orphan*/  privdata; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ dict ;

/* Variables and functions */
 int DICT_ERR ; 
 int DICT_OK ; 
 int /*<<< orphan*/  _dictInit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long _dictNextPower (unsigned long) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__** calloc (unsigned long,int) ; 
 unsigned int dictHashKey (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 

__attribute__((used)) static int dictExpand(dict *ht, unsigned long size) {
    dict n; /* the new hashtable */
    unsigned long realsize = _dictNextPower(size), i;

    /* the size is invalid if it is smaller than the number of
     * elements already inside the hashtable */
    if (ht->used > size)
        return DICT_ERR;

    _dictInit(&n, ht->type, ht->privdata);
    n.size = realsize;
    n.sizemask = realsize-1;
    n.table = calloc(realsize,sizeof(dictEntry*));

    /* Copy all the elements from the old to the new table:
     * note that if the old hash table is empty ht->size is zero,
     * so dictExpand just creates an hash table. */
    n.used = ht->used;
    for (i = 0; i < ht->size && ht->used > 0; i++) {
        dictEntry *he, *nextHe;

        if (ht->table[i] == NULL) continue;

        /* For each hash entry on this slot... */
        he = ht->table[i];
        while(he) {
            unsigned int h;

            nextHe = he->next;
            /* Get the new element index */
            h = dictHashKey(ht, he->key) & n.sizemask;
            he->next = n.table[h];
            n.table[h] = he;
            ht->used--;
            /* Pass to the next element */
            he = nextHe;
        }
    }
    assert(ht->used == 0);
    free(ht->table);

    /* Remap the new hashtable in the old */
    *ht = n;
    return DICT_OK;
}