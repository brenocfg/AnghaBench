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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_COMMENT_CLOSE_BRACE ; 
 int /*<<< orphan*/  AML_COMMENT_ENDBLK ; 
 int /*<<< orphan*/  AcpiGbl_CaptureComments ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*) ; 
 int /*<<< orphan*/  CvPrintOneCommentType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
CvCloseBraceWriteComment(
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level)
{

    if (!AcpiGbl_CaptureComments)
    {
        AcpiOsPrintf ("}");
        return;
    }

    CvPrintOneCommentType (Op, AML_COMMENT_ENDBLK, NULL, Level);
    AcpiOsPrintf ("}");
    CvPrintOneCommentType (Op, AML_COMMENT_CLOSE_BRACE, NULL, Level);
}