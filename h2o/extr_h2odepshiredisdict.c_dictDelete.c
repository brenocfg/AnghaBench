#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* next; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ dictEntry ;
struct TYPE_12__ {scalar_t__ size; unsigned int sizemask; int /*<<< orphan*/  used; TYPE_1__** table; } ;
typedef  TYPE_2__ dict ;

/* Variables and functions */
 int DICT_ERR ; 
 int DICT_OK ; 
 scalar_t__ dictCompareHashKeys (TYPE_2__*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dictFreeEntryKey (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  dictFreeEntryVal (TYPE_2__*,TYPE_1__*) ; 
 unsigned int dictHashKey (TYPE_2__*,void const*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static int dictDelete(dict *ht, const void *key) {
    unsigned int h;
    dictEntry *de, *prevde;

    if (ht->size == 0)
        return DICT_ERR;
    h = dictHashKey(ht, key) & ht->sizemask;
    de = ht->table[h];

    prevde = NULL;
    while(de) {
        if (dictCompareHashKeys(ht,key,de->key)) {
            /* Unlink the element from the list */
            if (prevde)
                prevde->next = de->next;
            else
                ht->table[h] = de->next;

            dictFreeEntryKey(ht,de);
            dictFreeEntryVal(ht,de);
            free(de);
            ht->used--;
            return DICT_OK;
        }
        prevde = de;
        de = de->next;
    }
    return DICT_ERR; /* not found */
}