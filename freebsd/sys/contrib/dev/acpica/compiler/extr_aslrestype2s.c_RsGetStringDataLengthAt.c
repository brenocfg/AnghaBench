#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  String; } ;
struct TYPE_8__ {scalar_t__ ParseOpcode; TYPE_1__ Value; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 TYPE_3__* ASL_GET_PEER_NODE (TYPE_3__*) ; 
 scalar_t__ PARSEOP_STRING_LITERAL ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT16
RsGetStringDataLengthAt (
    ACPI_PARSE_OBJECT       *InitializerOp,
    UINT32                  StartIndex)
{
    UINT32 i;

    for (i = 0; InitializerOp; i++)
    {
        if (i == StartIndex &&
            InitializerOp->Asl.ParseOpcode == PARSEOP_STRING_LITERAL)
        {
            return ((UINT16) (strlen (InitializerOp->Asl.Value.String) + 1));
        }

        InitializerOp = ASL_GET_PEER_NODE (InitializerOp);
    }

    return (0);
}