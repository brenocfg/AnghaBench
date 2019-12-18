#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct heim_base {int ref_cnt; int /*<<< orphan*/  isa; } ;
typedef  int /*<<< orphan*/  heim_type_t ;
typedef  int /*<<< orphan*/ * heim_object_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BASE2PTR (struct heim_base*) ; 
 struct heim_base* calloc (int,size_t) ; 

heim_object_t
_heim_alloc_object(heim_type_t type, size_t size)
{
    /* XXX should use posix_memalign */
    struct heim_base *p = calloc(1, size + sizeof(*p));
    if (p == NULL)
	return NULL;
    p->isa = type;
    p->ref_cnt = 1;

    return BASE2PTR(p);
}