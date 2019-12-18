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
struct TYPE_4__ {int /*<<< orphan*/ * EndBlkComment; int /*<<< orphan*/ * CommentList; int /*<<< orphan*/ * CloseBraceComment; int /*<<< orphan*/ * EndNodeComment; int /*<<< orphan*/ * InlineComment; } ;
struct TYPE_5__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * AcpiGbl_CurrentCloseBraceComment ; 
 int /*<<< orphan*/ * AcpiGbl_CurrentEndNodeComment ; 
 int /*<<< orphan*/ * AcpiGbl_CurrentInlineComment ; 
 int /*<<< orphan*/ * AcpiGbl_EndBlkCommentListHead ; 
 int /*<<< orphan*/ * AcpiGbl_EndBlkCommentListTail ; 
 int /*<<< orphan*/ * AcpiGbl_RegCommentListHead ; 
 int /*<<< orphan*/ * AcpiGbl_RegCommentListTail ; 

void
CvTransferComments (
    ACPI_PARSE_OBJECT       *Op)
{

    Op->Common.InlineComment = AcpiGbl_CurrentInlineComment;
    AcpiGbl_CurrentInlineComment = NULL;

    Op->Common.EndNodeComment = AcpiGbl_CurrentEndNodeComment;
    AcpiGbl_CurrentEndNodeComment = NULL;

    Op->Common.CloseBraceComment = AcpiGbl_CurrentCloseBraceComment;
    AcpiGbl_CurrentCloseBraceComment = NULL;

    Op->Common.CommentList = AcpiGbl_RegCommentListHead;
    AcpiGbl_RegCommentListHead = NULL;
    AcpiGbl_RegCommentListTail = NULL;

    Op->Common.EndBlkComment = AcpiGbl_EndBlkCommentListHead;
    AcpiGbl_EndBlkCommentListHead = NULL;
    AcpiGbl_EndBlkCommentListTail = NULL;
}