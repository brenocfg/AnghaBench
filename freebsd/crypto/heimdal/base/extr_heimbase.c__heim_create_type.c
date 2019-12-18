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
typedef  TYPE_1__* heim_type_t ;
typedef  int /*<<< orphan*/  heim_type_init ;
typedef  int /*<<< orphan*/  heim_type_hash ;
typedef  int /*<<< orphan*/  heim_type_dealloc ;
typedef  int /*<<< orphan*/  heim_type_copy ;
typedef  int /*<<< orphan*/  heim_type_cmp ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/  hash; int /*<<< orphan*/  cmp; int /*<<< orphan*/  copy; int /*<<< orphan*/  dealloc; int /*<<< orphan*/  init; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  heim_base_atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tidglobal ; 

heim_type_t
_heim_create_type(const char *name,
		  heim_type_init init,
		  heim_type_dealloc dealloc,
		  heim_type_copy copy,
		  heim_type_cmp cmp,
		  heim_type_hash hash)
{
    heim_type_t type;

    type = calloc(1, sizeof(*type));
    if (type == NULL)
	return NULL;

    type->tid = heim_base_atomic_inc(&tidglobal);
    type->name = name;
    type->init = init;
    type->dealloc = dealloc;
    type->copy = copy;
    type->cmp = cmp;
    type->hash = hash;

    return type;
}