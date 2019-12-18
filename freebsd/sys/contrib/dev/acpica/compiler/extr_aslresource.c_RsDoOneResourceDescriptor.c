#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_92__   TYPE_86__ ;
typedef  struct TYPE_91__   TYPE_5__ ;
typedef  struct TYPE_90__   TYPE_4__ ;
typedef  struct TYPE_89__   TYPE_3__ ;
typedef  struct TYPE_88__   TYPE_2__ ;
typedef  struct TYPE_87__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_87__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_88__ {int ParseOpcode; char* ParseOpName; int /*<<< orphan*/  Extra; int /*<<< orphan*/  FinalAmlLength; TYPE_1__ Value; int /*<<< orphan*/  CompileFlags; } ;
struct TYPE_92__ {TYPE_2__ Asl; } ;
struct TYPE_91__ {int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_90__ {TYPE_86__* DescriptorTypeOp; int /*<<< orphan*/  CurrentByteOffset; } ;
struct TYPE_89__ {scalar_t__ Buffer; int /*<<< orphan*/  BufferLength; } ;
typedef  TYPE_3__ ASL_RESOURCE_NODE ;
typedef  TYPE_4__ ASL_RESOURCE_INFO ;
typedef  TYPE_5__ AML_RESOURCE ;

/* Variables and functions */
#define  ACPI_RSTATE_DEPENDENT_LIST 173 
#define  ACPI_RSTATE_NORMAL 172 
#define  ACPI_RSTATE_START_DEPENDENT 171 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_DEPENDENT_NESTING ; 
 int /*<<< orphan*/  ASL_MSG_MISSING_STARTDEPENDENT ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_86__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP_IS_RESOURCE_DESC ; 
#define  PARSEOP_DEFAULT_ARG 170 
#define  PARSEOP_DMA 169 
#define  PARSEOP_DWORDIO 168 
#define  PARSEOP_DWORDMEMORY 167 
#define  PARSEOP_DWORDSPACE 166 
#define  PARSEOP_ENDDEPENDENTFN 165 
#define  PARSEOP_ENDTAG 164 
#define  PARSEOP_EXTENDEDIO 163 
#define  PARSEOP_EXTENDEDMEMORY 162 
#define  PARSEOP_EXTENDEDSPACE 161 
#define  PARSEOP_FIXEDDMA 160 
#define  PARSEOP_FIXEDIO 159 
#define  PARSEOP_GPIO_INT 158 
#define  PARSEOP_GPIO_IO 157 
#define  PARSEOP_I2C_SERIALBUS 156 
#define  PARSEOP_I2C_SERIALBUS_V2 155 
#define  PARSEOP_INTERRUPT 154 
#define  PARSEOP_IO 153 
#define  PARSEOP_IRQ 152 
#define  PARSEOP_IRQNOFLAGS 151 
#define  PARSEOP_MEMORY24 150 
#define  PARSEOP_MEMORY32 149 
#define  PARSEOP_MEMORY32FIXED 148 
#define  PARSEOP_PINCONFIG 147 
#define  PARSEOP_PINFUNCTION 146 
#define  PARSEOP_PINGROUP 145 
#define  PARSEOP_PINGROUPCONFIG 144 
#define  PARSEOP_PINGROUPFUNCTION 143 
#define  PARSEOP_QWORDIO 142 
#define  PARSEOP_QWORDMEMORY 141 
#define  PARSEOP_QWORDSPACE 140 
#define  PARSEOP_REGISTER 139 
#define  PARSEOP_SPI_SERIALBUS 138 
#define  PARSEOP_SPI_SERIALBUS_V2 137 
#define  PARSEOP_STARTDEPENDENTFN 136 
#define  PARSEOP_STARTDEPENDENTFN_NOPRI 135 
#define  PARSEOP_UART_SERIALBUS 134 
#define  PARSEOP_UART_SERIALBUS_V2 133 
#define  PARSEOP_VENDORLONG 132 
#define  PARSEOP_VENDORSHORT 131 
#define  PARSEOP_WORDBUSNUMBER 130 
#define  PARSEOP_WORDIO 129 
#define  PARSEOP_WORDSPACE 128 
 TYPE_3__* RsDoDmaDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoDwordIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoDwordMemoryDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoDwordSpaceDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoEndDependentDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoEndTagDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoExtendedIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoExtendedMemoryDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoExtendedSpaceDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoFixedDmaDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoFixedIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoGeneralRegisterDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoGpioIntDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoGpioIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoI2cSerialBusDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoInterruptDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoIrqDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoIrqNoFlagsDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoMemory24Descriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoMemory32Descriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoMemory32FixedDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoPinConfigDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoPinFunctionDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoPinGroupConfigDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoPinGroupDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoPinGroupFunctionDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoQwordIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoQwordMemoryDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoQwordSpaceDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoSpiSerialBusDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoStartDependentDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoStartDependentNoPriDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoUartSerialBusDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoVendorLargeDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoVendorSmallDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoWordBusNumberDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoWordIoDescriptor (TYPE_4__*) ; 
 TYPE_3__* RsDoWordSpaceDescriptor (TYPE_4__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

ASL_RESOURCE_NODE *
RsDoOneResourceDescriptor (
    ASL_RESOURCE_INFO       *Info,
    UINT8                   *State)
{
    ASL_RESOURCE_NODE       *Rnode = NULL;


    /* Construct the resource */

    switch (Info->DescriptorTypeOp->Asl.ParseOpcode)
    {
    case PARSEOP_DMA:

        Rnode = RsDoDmaDescriptor (Info);
        break;

    case PARSEOP_FIXEDDMA:

        Rnode = RsDoFixedDmaDescriptor (Info);
        break;

    case PARSEOP_DWORDIO:

        Rnode = RsDoDwordIoDescriptor (Info);
        break;

    case PARSEOP_DWORDMEMORY:

        Rnode = RsDoDwordMemoryDescriptor (Info);
        break;

    case PARSEOP_DWORDSPACE:

        Rnode = RsDoDwordSpaceDescriptor (Info);
        break;

    case PARSEOP_ENDDEPENDENTFN:

        switch (*State)
        {
        case ACPI_RSTATE_NORMAL:

            AslError (ASL_ERROR, ASL_MSG_MISSING_STARTDEPENDENT,
                Info->DescriptorTypeOp, NULL);
            break;

        case ACPI_RSTATE_START_DEPENDENT:

            AslError (ASL_ERROR, ASL_MSG_DEPENDENT_NESTING,
                Info->DescriptorTypeOp, NULL);
            break;

        case ACPI_RSTATE_DEPENDENT_LIST:
        default:

            break;
        }

        *State = ACPI_RSTATE_NORMAL;
        Rnode = RsDoEndDependentDescriptor (Info);
        break;

    case PARSEOP_ENDTAG:

        Rnode = RsDoEndTagDescriptor (Info);
        break;

    case PARSEOP_EXTENDEDIO:

        Rnode = RsDoExtendedIoDescriptor (Info);
        break;

    case PARSEOP_EXTENDEDMEMORY:

        Rnode = RsDoExtendedMemoryDescriptor (Info);
        break;

    case PARSEOP_EXTENDEDSPACE:

        Rnode = RsDoExtendedSpaceDescriptor (Info);
        break;

    case PARSEOP_FIXEDIO:

        Rnode = RsDoFixedIoDescriptor (Info);
        break;

    case PARSEOP_INTERRUPT:

        Rnode = RsDoInterruptDescriptor (Info);
        break;

    case PARSEOP_IO:

        Rnode = RsDoIoDescriptor (Info);
        break;

    case PARSEOP_IRQ:

        Rnode = RsDoIrqDescriptor (Info);
        break;

    case PARSEOP_IRQNOFLAGS:

        Rnode = RsDoIrqNoFlagsDescriptor (Info);
        break;

    case PARSEOP_MEMORY24:

        Rnode = RsDoMemory24Descriptor (Info);
        break;

    case PARSEOP_MEMORY32:

        Rnode = RsDoMemory32Descriptor (Info);
        break;

    case PARSEOP_MEMORY32FIXED:

        Rnode = RsDoMemory32FixedDescriptor (Info);
        break;

    case PARSEOP_QWORDIO:

        Rnode = RsDoQwordIoDescriptor (Info);
        break;

    case PARSEOP_QWORDMEMORY:

        Rnode = RsDoQwordMemoryDescriptor (Info);
        break;

    case PARSEOP_QWORDSPACE:

        Rnode = RsDoQwordSpaceDescriptor (Info);
        break;

    case PARSEOP_REGISTER:

        Rnode = RsDoGeneralRegisterDescriptor (Info);
        break;

    case PARSEOP_STARTDEPENDENTFN:

        switch (*State)
        {
        case ACPI_RSTATE_START_DEPENDENT:

            AslError (ASL_ERROR, ASL_MSG_DEPENDENT_NESTING,
                Info->DescriptorTypeOp, NULL);
            break;

        case ACPI_RSTATE_NORMAL:
        case ACPI_RSTATE_DEPENDENT_LIST:
        default:

            break;
        }

        *State = ACPI_RSTATE_START_DEPENDENT;
        Rnode = RsDoStartDependentDescriptor (Info);
        *State = ACPI_RSTATE_DEPENDENT_LIST;
        break;

    case PARSEOP_STARTDEPENDENTFN_NOPRI:

        switch (*State)
        {
        case ACPI_RSTATE_START_DEPENDENT:

            AslError (ASL_ERROR, ASL_MSG_DEPENDENT_NESTING,
                Info->DescriptorTypeOp, NULL);
            break;

        case ACPI_RSTATE_NORMAL:
        case ACPI_RSTATE_DEPENDENT_LIST:
        default:

            break;
        }

        *State = ACPI_RSTATE_START_DEPENDENT;
        Rnode = RsDoStartDependentNoPriDescriptor (Info);
        *State = ACPI_RSTATE_DEPENDENT_LIST;
        break;

    case PARSEOP_VENDORLONG:

        Rnode = RsDoVendorLargeDescriptor (Info);
        break;

    case PARSEOP_VENDORSHORT:

        Rnode = RsDoVendorSmallDescriptor (Info);
        break;

    case PARSEOP_WORDBUSNUMBER:

        Rnode = RsDoWordBusNumberDescriptor (Info);
        break;

    case PARSEOP_WORDIO:

        Rnode = RsDoWordIoDescriptor (Info);
        break;

    case PARSEOP_WORDSPACE:

        Rnode = RsDoWordSpaceDescriptor (Info);
        break;

    case PARSEOP_GPIO_INT:

        Rnode = RsDoGpioIntDescriptor (Info);
        break;

    case PARSEOP_GPIO_IO:

        Rnode = RsDoGpioIoDescriptor (Info);
        break;

    case PARSEOP_I2C_SERIALBUS:
    case PARSEOP_I2C_SERIALBUS_V2:

        Rnode = RsDoI2cSerialBusDescriptor (Info);
        break;

    case PARSEOP_SPI_SERIALBUS:
    case PARSEOP_SPI_SERIALBUS_V2:

        Rnode = RsDoSpiSerialBusDescriptor (Info);
        break;

    case PARSEOP_UART_SERIALBUS:
    case PARSEOP_UART_SERIALBUS_V2:

        Rnode = RsDoUartSerialBusDescriptor (Info);
        break;

    case PARSEOP_PINCONFIG:

        Rnode = RsDoPinConfigDescriptor (Info);
        break;

    case PARSEOP_PINFUNCTION:

        Rnode = RsDoPinFunctionDescriptor (Info);
        break;

    case PARSEOP_PINGROUP:

        Rnode = RsDoPinGroupDescriptor (Info);
        break;

    case PARSEOP_PINGROUPFUNCTION:

        Rnode = RsDoPinGroupFunctionDescriptor (Info);
        break;

    case PARSEOP_PINGROUPCONFIG:

        Rnode = RsDoPinGroupConfigDescriptor (Info);
        break;

    case PARSEOP_DEFAULT_ARG:

        /* Just ignore any of these, they are used as fillers/placeholders */
        break;

    default:

        printf ("Unknown resource descriptor type [%s]\n",
            Info->DescriptorTypeOp->Asl.ParseOpName);
        break;
    }

    /*
     * Mark original node as unused, but head of a resource descriptor.
     * This allows the resource to be installed in the namespace so that
     * references to the descriptor can be resolved.
     */
    Info->DescriptorTypeOp->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    Info->DescriptorTypeOp->Asl.CompileFlags = OP_IS_RESOURCE_DESC;
    Info->DescriptorTypeOp->Asl.Value.Integer = Info->CurrentByteOffset;

    if (Rnode)
    {
        Info->DescriptorTypeOp->Asl.FinalAmlLength = Rnode->BufferLength;
        Info->DescriptorTypeOp->Asl.Extra =
            ((AML_RESOURCE *) Rnode->Buffer)->DescriptorType;
    }

    return (Rnode);
}