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

/* Variables and functions */
 int /*<<< orphan*/  AslGbl_CurrentLineBuffer ; 
 int /*<<< orphan*/  AslGbl_ExpressionTokenBuffer ; 
 int /*<<< orphan*/  AslGbl_MacroTokenBuffer ; 
 int /*<<< orphan*/  AslGbl_MainTokenBuffer ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
UtFreeLineBuffers (
    void)
{

    free (AslGbl_CurrentLineBuffer);
    free (AslGbl_MainTokenBuffer);
    free (AslGbl_MacroTokenBuffer);
    free (AslGbl_ExpressionTokenBuffer);
}