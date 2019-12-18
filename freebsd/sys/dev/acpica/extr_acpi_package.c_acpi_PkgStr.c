#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t Length; void* Pointer; } ;
struct TYPE_8__ {size_t Length; void* Pointer; } ;
struct TYPE_7__ {TYPE_4__* Elements; } ;
struct TYPE_9__ {int Type; TYPE_1__ Buffer; TYPE_3__ String; TYPE_2__ Package; } ;
typedef  TYPE_4__ ACPI_OBJECT ;

/* Variables and functions */
#define  ACPI_TYPE_BUFFER 129 
#define  ACPI_TYPE_STRING 128 
 int E2BIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  strlcpy (void*,void*,size_t) ; 

int
acpi_PkgStr(ACPI_OBJECT *res, int idx, void *dst, size_t size)
{
    ACPI_OBJECT		*obj;
    void		*ptr;
    size_t		 length;

    obj = &res->Package.Elements[idx];
    if (obj == NULL)
	return (EINVAL);

    switch (obj->Type) {
    case ACPI_TYPE_STRING:
	ptr = obj->String.Pointer;
	length = obj->String.Length;
	break;
    case ACPI_TYPE_BUFFER:
	ptr = obj->Buffer.Pointer;
	length = obj->Buffer.Length;
	break;
    default:
	return (EINVAL);
    }

    /* Make sure string will fit, including terminating NUL */
    if (++length > size)
	return (E2BIG);

    strlcpy(dst, ptr, length);
    return (0);
}