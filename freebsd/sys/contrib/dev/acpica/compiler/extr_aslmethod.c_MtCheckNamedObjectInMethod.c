#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ Class; } ;
struct TYPE_8__ {scalar_t__ AmlOpcode; } ;
struct TYPE_10__ {TYPE_1__ Asl; } ;
struct TYPE_9__ {void* ShouldBeSerialized; int /*<<< orphan*/  Op; void* CreatesNamedObjects; } ;
typedef  TYPE_2__ ASL_METHOD_INFO ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  TYPE_4__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 scalar_t__ AML_CLASS_NAMED_OBJECT ; 
 scalar_t__ AML_METHOD_OP ; 
 scalar_t__ AML_SCOPE_OP ; 
 int /*<<< orphan*/  ASL_MSG_SERIALIZED_REQUIRED ; 
 int /*<<< orphan*/  ASL_REMARK ; 
 TYPE_4__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* TRUE ; 

__attribute__((used)) static void
MtCheckNamedObjectInMethod (
    ACPI_PARSE_OBJECT       *Op,
    ASL_METHOD_INFO         *MethodInfo)
{
    const ACPI_OPCODE_INFO  *OpInfo;


    /* We don't care about actual method declarations or scopes */

    if ((Op->Asl.AmlOpcode == AML_METHOD_OP) ||
        (Op->Asl.AmlOpcode == AML_SCOPE_OP))
    {
        return;
    }

    /* Determine if we are creating a named object within a method */

    if (!MethodInfo)
    {
        return;
    }

    OpInfo = AcpiPsGetOpcodeInfo (Op->Asl.AmlOpcode);
    if (OpInfo->Class == AML_CLASS_NAMED_OBJECT)
    {
        /*
         * 1) Mark the method as a method that creates named objects.
         *
         * 2) If the method is non-serialized, emit a remark that the method
         * should be serialized.
         *
         * Reason: If a thread blocks within the method for any reason, and
         * another thread enters the method, the method will fail because
         * an attempt will be made to create the same object twice.
         */
        MethodInfo->CreatesNamedObjects = TRUE;
        if (!MethodInfo->ShouldBeSerialized)
        {
            AslError (ASL_REMARK, ASL_MSG_SERIALIZED_REQUIRED, MethodInfo->Op,
                "due to creation of named objects within");

            /* Emit message only ONCE per method */

            MethodInfo->ShouldBeSerialized = TRUE;
        }
    }
}