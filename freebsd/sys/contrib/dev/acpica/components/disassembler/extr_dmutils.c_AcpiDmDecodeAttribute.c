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
typedef  int UINT8 ;

/* Variables and functions */
#define  AML_FIELD_ATTRIB_BLOCK 137 
#define  AML_FIELD_ATTRIB_BLOCK_PROCESS_CALL 136 
#define  AML_FIELD_ATTRIB_BYTE 135 
#define  AML_FIELD_ATTRIB_BYTES 134 
#define  AML_FIELD_ATTRIB_PROCESS_CALL 133 
#define  AML_FIELD_ATTRIB_QUICK 132 
#define  AML_FIELD_ATTRIB_RAW_BYTES 131 
#define  AML_FIELD_ATTRIB_RAW_PROCESS_BYTES 130 
#define  AML_FIELD_ATTRIB_SEND_RECEIVE 129 
#define  AML_FIELD_ATTRIB_WORD 128 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 

void
AcpiDmDecodeAttribute (
    UINT8                   Attribute)
{

    switch (Attribute)
    {
    case AML_FIELD_ATTRIB_QUICK:

        AcpiOsPrintf ("AttribQuick");
        break;

    case AML_FIELD_ATTRIB_SEND_RECEIVE:

        AcpiOsPrintf ("AttribSendReceive");
        break;

    case AML_FIELD_ATTRIB_BYTE:

        AcpiOsPrintf ("AttribByte");
        break;

    case AML_FIELD_ATTRIB_WORD:

        AcpiOsPrintf ("AttribWord");
        break;

    case AML_FIELD_ATTRIB_BLOCK:

        AcpiOsPrintf ("AttribBlock");
        break;

    case AML_FIELD_ATTRIB_BYTES:

        AcpiOsPrintf ("AttribBytes");
        break;

    case AML_FIELD_ATTRIB_PROCESS_CALL:

        AcpiOsPrintf ("AttribProcessCall");
        break;

    case AML_FIELD_ATTRIB_BLOCK_PROCESS_CALL:

        AcpiOsPrintf ("AttribBlockProcessCall");
        break;

    case AML_FIELD_ATTRIB_RAW_BYTES:

        AcpiOsPrintf ("AttribRawBytes");
        break;

    case AML_FIELD_ATTRIB_RAW_PROCESS_BYTES:

        AcpiOsPrintf ("AttribRawProcessBytes");
        break;

    default:

        /* A ByteConst is allowed by the grammar */

        AcpiOsPrintf ("0x%2.2X", Attribute);
        break;
    }
}