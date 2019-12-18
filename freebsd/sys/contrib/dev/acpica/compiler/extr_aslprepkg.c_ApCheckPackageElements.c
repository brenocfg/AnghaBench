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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
struct TYPE_6__ {TYPE_2__* Next; } ;
struct TYPE_7__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ApCheckObjectType (char const*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ACPI_PARSE_OBJECT *
ApCheckPackageElements (
    const char              *PredefinedName,
    ACPI_PARSE_OBJECT       *Op,
    UINT8                   Type1,
    UINT32                  Count1,
    UINT8                   Type2,
    UINT32                  Count2)
{
    UINT32                  i;


    /*
     * Up to two groups of package elements are supported by the data
     * structure. All elements in each group must be of the same type.
     * The second group can have a count of zero.
     *
     * Aborts check upon a NULL package element, as this means (at compile
     * time) that the remainder of the package elements are also NULL
     * (This is the only way to create NULL package elements.)
     */
    for (i = 0; (i < Count1) && Op; i++)
    {
        ApCheckObjectType (PredefinedName, Op, Type1, i);
        Op = Op->Asl.Next;
    }

    for (i = 0; (i < Count2) && Op; i++)
    {
        ApCheckObjectType (PredefinedName, Op, Type2, (i + Count1));
        Op = Op->Asl.Next;
    }

    return (Op);
}