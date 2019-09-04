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
struct TYPE_4__ {size_t count; struct TYPE_4__* elems; struct TYPE_4__* value; struct TYPE_4__* key; } ;
typedef  TYPE_1__ IjkAVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  ijk_av_freep (TYPE_1__**) ; 

void ijk_av_dict_free(IjkAVDictionary **pm)
{
    IjkAVDictionary *m = *pm;

    if (m) {
        while (m->count--) {
            ijk_av_freep(&m->elems[m->count].key);
            ijk_av_freep(&m->elems[m->count].value);
        }
        ijk_av_freep(&m->elems);
    }
    ijk_av_freep(pm);
}