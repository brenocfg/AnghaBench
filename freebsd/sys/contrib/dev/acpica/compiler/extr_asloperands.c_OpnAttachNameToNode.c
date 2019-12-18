#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int AmlOpcode; } ;
struct TYPE_9__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
#define  AML_ALIAS_OP 149 
#define  AML_BANK_FIELD_OP 148 
#define  AML_CREATE_BIT_FIELD_OP 147 
#define  AML_CREATE_BYTE_FIELD_OP 146 
#define  AML_CREATE_DWORD_FIELD_OP 145 
#define  AML_CREATE_FIELD_OP 144 
#define  AML_CREATE_QWORD_FIELD_OP 143 
#define  AML_CREATE_WORD_FIELD_OP 142 
#define  AML_DATA_REGION_OP 141 
#define  AML_DEVICE_OP 140 
#define  AML_EVENT_OP 139 
#define  AML_EXTERNAL_OP 138 
#define  AML_FIELD_OP 137 
#define  AML_INDEX_FIELD_OP 136 
#define  AML_METHOD_OP 135 
#define  AML_MUTEX_OP 134 
#define  AML_NAME_OP 133 
#define  AML_POWER_RESOURCE_OP 132 
#define  AML_PROCESSOR_OP 131 
#define  AML_REGION_OP 130 
#define  AML_SCOPE_OP 129 
#define  AML_THERMAL_ZONE_OP 128 
 int /*<<< orphan*/  UtAttachNamepathToOwner (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* UtGetArg (TYPE_2__*,int) ; 

__attribute__((used)) static void
OpnAttachNameToNode (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Child = NULL;


    switch (Op->Asl.AmlOpcode)
    {
    case AML_DATA_REGION_OP:
    case AML_DEVICE_OP:
    case AML_EVENT_OP:
    case AML_EXTERNAL_OP:
    case AML_METHOD_OP:
    case AML_MUTEX_OP:
    case AML_REGION_OP:
    case AML_POWER_RESOURCE_OP:
    case AML_PROCESSOR_OP:
    case AML_THERMAL_ZONE_OP:
    case AML_NAME_OP:
    case AML_SCOPE_OP:

        Child = UtGetArg (Op, 0);
        break;

    case AML_ALIAS_OP:

        Child = UtGetArg (Op, 1);
        break;

    case AML_CREATE_BIT_FIELD_OP:
    case AML_CREATE_BYTE_FIELD_OP:
    case AML_CREATE_WORD_FIELD_OP:
    case AML_CREATE_DWORD_FIELD_OP:
    case AML_CREATE_QWORD_FIELD_OP:

        Child = UtGetArg (Op, 2);
        break;

    case AML_CREATE_FIELD_OP:

        Child = UtGetArg (Op, 3);
        break;

    case AML_BANK_FIELD_OP:
    case AML_INDEX_FIELD_OP:
    case AML_FIELD_OP:

        return;

    default:

        return;
    }

    if (Child)
    {
        UtAttachNamepathToOwner (Op, Child);
    }
}