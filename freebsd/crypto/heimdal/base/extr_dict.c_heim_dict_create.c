#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* heim_dict_t ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/ * tab; } ;

/* Variables and functions */
 TYPE_1__* _heim_alloc_object (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 
 int /*<<< orphan*/  dict_object ; 
 scalar_t__ findprime (size_t) ; 
 int /*<<< orphan*/  heim_release (TYPE_1__*) ; 

heim_dict_t
heim_dict_create(size_t size)
{
    heim_dict_t dict;

    dict = _heim_alloc_object(&dict_object, sizeof(*dict));

    dict->size = findprime(size);
    if (dict->size == 0) {
	heim_release(dict);
	return NULL;
    }

    dict->tab = calloc(dict->size, sizeof(dict->tab[0]));
    if (dict->tab == NULL) {
	dict->size = 0;
	heim_release(dict);
	return NULL;
    }

    return dict;
}