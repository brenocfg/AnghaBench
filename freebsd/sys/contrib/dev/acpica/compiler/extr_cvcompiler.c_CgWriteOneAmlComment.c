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
typedef  char UINT8 ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  AML_COMMENT_OP ; 
 int /*<<< orphan*/  CgLocalWriteAmlData (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

void
CgWriteOneAmlComment(
    ACPI_PARSE_OBJECT       *Op,
    char*                   CommentToPrint,
    UINT8                   InputOption)
{
    UINT8                   CommentOption = InputOption;
    UINT8                   CommentOpcode = (UINT8) AML_COMMENT_OP;


    if (!CommentToPrint)
    {
        return;
    }

    CgLocalWriteAmlData (Op, &CommentOpcode, 1);
    CgLocalWriteAmlData (Op, &CommentOption, 1);

    /* The strlen (..) + 1 is to include the null terminator */

    CgLocalWriteAmlData (Op, CommentToPrint, strlen (CommentToPrint) + 1);
}