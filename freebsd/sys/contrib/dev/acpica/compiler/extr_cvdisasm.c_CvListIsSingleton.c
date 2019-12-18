#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ Next; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_1__ ACPI_COMMENT_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
CvListIsSingleton (
    ACPI_COMMENT_NODE       *CommentList)

{

    if (!CommentList)
    {
        return (FALSE);
    }
    else if (CommentList->Next)
    {
        return (FALSE);
    }

    return (TRUE);
}