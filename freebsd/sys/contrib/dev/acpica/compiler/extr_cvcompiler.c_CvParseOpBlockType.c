#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_4__ {int ParseOpcode; } ;
struct TYPE_5__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int BLOCK_BRACE ; 
 int BLOCK_NONE ; 
 int BLOCK_PAREN ; 
#define  PARSEOP_BANKFIELD 156 
#define  PARSEOP_BUFFER 155 
#define  PARSEOP_CASE 154 
#define  PARSEOP_DATABUFFER 153 
#define  PARSEOP_DEFINITION_BLOCK 152 
#define  PARSEOP_DEVICE 151 
#define  PARSEOP_DMA 150 
#define  PARSEOP_ELSEIF 149 
#define  PARSEOP_FIELD 148 
#define  PARSEOP_FOR 147 
#define  PARSEOP_FUNCTION 146 
#define  PARSEOP_GPIO_INT 145 
#define  PARSEOP_GPIO_IO 144 
#define  PARSEOP_IF 143 
#define  PARSEOP_INDEXFIELD 142 
#define  PARSEOP_INTERRUPT 141 
#define  PARSEOP_IRQ 140 
#define  PARSEOP_IRQNOFLAGS 139 
#define  PARSEOP_METHOD 138 
#define  PARSEOP_POWERRESOURCE 137 
#define  PARSEOP_PROCESSOR 136 
#define  PARSEOP_RESOURCETEMPLATE 135 
#define  PARSEOP_SCOPE 134 
#define  PARSEOP_SWITCH 133 
#define  PARSEOP_THERMALZONE 132 
#define  PARSEOP_VAR_PACKAGE 131 
#define  PARSEOP_VENDORLONG 130 
#define  PARSEOP_VENDORSHORT 129 
#define  PARSEOP_WHILE 128 

UINT32
CvParseOpBlockType (
    ACPI_PARSE_OBJECT       *Op)
{

    if (!Op)
    {
        return (BLOCK_NONE);
    }

    switch (Op->Asl.ParseOpcode)
    {
    /* From aslprimaries.y */

    case PARSEOP_VAR_PACKAGE:
    case PARSEOP_BANKFIELD:
    case PARSEOP_BUFFER:
    case PARSEOP_CASE:
    case PARSEOP_DEVICE:
    case PARSEOP_FIELD:
    case PARSEOP_FOR:
    case PARSEOP_FUNCTION:
    case PARSEOP_IF:
    case PARSEOP_ELSEIF:
    case PARSEOP_INDEXFIELD:
    case PARSEOP_METHOD:
    case PARSEOP_POWERRESOURCE:
    case PARSEOP_PROCESSOR:
    case PARSEOP_DATABUFFER:
    case PARSEOP_SCOPE:
    case PARSEOP_SWITCH:
    case PARSEOP_THERMALZONE:
    case PARSEOP_WHILE:

    /* From aslresources.y */

    case PARSEOP_RESOURCETEMPLATE: /* optional parens */
    case PARSEOP_VENDORLONG:
    case PARSEOP_VENDORSHORT:
    case PARSEOP_INTERRUPT:
    case PARSEOP_IRQNOFLAGS:
    case PARSEOP_IRQ:
    case PARSEOP_GPIO_INT:
    case PARSEOP_GPIO_IO:
    case PARSEOP_DMA:

    /* From aslrules.y */

    case PARSEOP_DEFINITION_BLOCK:
        return (BLOCK_PAREN | BLOCK_BRACE);

    default:
        return (BLOCK_NONE);
    }
}