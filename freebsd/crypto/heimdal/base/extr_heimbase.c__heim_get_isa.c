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
struct heim_base {int /*<<< orphan*/  isa; } ;
typedef  int /*<<< orphan*/  heim_type_t ;
typedef  int /*<<< orphan*/  heim_object_t ;

/* Variables and functions */
 struct heim_base* PTR2BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_abort (char*) ; 
 scalar_t__ heim_base_is_tagged (int /*<<< orphan*/ ) ; 
 scalar_t__ heim_base_is_tagged_object (int /*<<< orphan*/ ) ; 
 size_t heim_base_tagged_object_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tagged_isa ; 

heim_type_t
_heim_get_isa(heim_object_t ptr)
{
    struct heim_base *p;
    if (heim_base_is_tagged(ptr)) {
	if (heim_base_is_tagged_object(ptr))
	    return tagged_isa[heim_base_tagged_object_tid(ptr)];
	heim_abort("not a supported tagged type");
    }
    p = PTR2BASE(ptr);
    return p->isa;
}