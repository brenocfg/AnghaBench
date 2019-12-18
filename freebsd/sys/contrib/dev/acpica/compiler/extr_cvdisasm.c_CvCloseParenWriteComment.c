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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {scalar_t__ AmlOpcode; TYPE_2__* Parent; scalar_t__ EndNodeComment; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_COMMENT_ENDBLK ; 
 int /*<<< orphan*/  AML_COMMENT_END_NODE ; 
 scalar_t__ AML_IF_OP ; 
 scalar_t__ AcpiDmBlockType (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiGbl_CaptureComments ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 scalar_t__ BLOCK_PAREN ; 
 int /*<<< orphan*/  CvPrintOneCommentType (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
CvCloseParenWriteComment(
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level)
{

    if (!AcpiGbl_CaptureComments)
    {
        AcpiOsPrintf (")");
        return;
    }

    /*
     * If this op has a BLOCK_BRACE, then output the comment when the
     * disassembler calls CvCloseBraceWriteComment
     */
    if (AcpiDmBlockType (Op) == BLOCK_PAREN)
    {
        CvPrintOneCommentType (Op, AML_COMMENT_ENDBLK, NULL, Level);
    }

    AcpiOsPrintf (")");

    if (Op->Common.EndNodeComment)
    {
        CvPrintOneCommentType (Op, AML_COMMENT_END_NODE, NULL, Level);
    }
    else if ((Op->Common.Parent->Common.AmlOpcode == AML_IF_OP) &&
         Op->Common.Parent->Common.EndNodeComment)
    {
        CvPrintOneCommentType (Op->Common.Parent,
            AML_COMMENT_END_NODE, NULL, Level);
    }
}