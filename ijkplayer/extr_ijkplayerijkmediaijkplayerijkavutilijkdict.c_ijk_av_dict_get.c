#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int count; TYPE_1__ const* elems; } ;
struct TYPE_6__ {char* key; } ;
typedef  TYPE_1__ const IjkAVDictionaryEntry ;
typedef  TYPE_2__ IjkAVDictionary ;

/* Variables and functions */
 int IJK_AV_DICT_IGNORE_SUFFIX ; 
 int IJK_AV_DICT_MATCH_CASE ; 
 scalar_t__ toupper (char const) ; 

IjkAVDictionaryEntry *ijk_av_dict_get(const IjkAVDictionary *m, const char *key,
                               const IjkAVDictionaryEntry *prev, int flags)
{
    unsigned int i, j;

    if (!m)
        return NULL;

    if (prev)
        i = prev - m->elems + 1;
    else
        i = 0;

    for (; i < m->count; i++) {
        const char *s = m->elems[i].key;
        if (flags & IJK_AV_DICT_MATCH_CASE)
            for (j = 0; s[j] == key[j] && key[j]; j++)
                ;
        else
            for (j = 0; toupper(s[j]) == toupper(key[j]) && key[j]; j++)
                ;
        if (key[j])
            continue;
        if (s[j] && !(flags & IJK_AV_DICT_IGNORE_SUFFIX))
            continue;
        return &m->elems[i];
    }
    return NULL;
}