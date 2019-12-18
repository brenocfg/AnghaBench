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
struct TYPE_4__ {int /*<<< orphan*/ * CvParentFilename; int /*<<< orphan*/ * CvFilename; int /*<<< orphan*/ * CloseBraceComment; int /*<<< orphan*/ * EndBlkComment; int /*<<< orphan*/ * CommentList; int /*<<< orphan*/ * NameComment; int /*<<< orphan*/ * EndNodeComment; int /*<<< orphan*/ * InlineComment; } ;
struct TYPE_5__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */

void
CvClearOpComments (
    ACPI_PARSE_OBJECT       *Op)
{

    Op->Common.InlineComment     = NULL;
    Op->Common.EndNodeComment    = NULL;
    Op->Common.NameComment       = NULL;
    Op->Common.CommentList       = NULL;
    Op->Common.EndBlkComment     = NULL;
    Op->Common.CloseBraceComment = NULL;
    Op->Common.CvFilename        = NULL;
    Op->Common.CvParentFilename  = NULL;
}