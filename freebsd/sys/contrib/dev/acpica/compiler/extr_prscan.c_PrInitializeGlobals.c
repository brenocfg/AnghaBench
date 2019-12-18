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
 int AslGbl_CurrentLineNumber ; 
 int /*<<< orphan*/ * AslGbl_DirectiveStack ; 
 scalar_t__ AslGbl_IfDepth ; 
 void* AslGbl_IgnoringThisCodeBlock ; 
 int /*<<< orphan*/ * AslGbl_InputFileList ; 
 void* AslGbl_PreprocessorError ; 
 int AslGbl_PreprocessorLineNumber ; 
 void* FALSE ; 

void
PrInitializeGlobals (
    void)
{
    /* Init globals */

    AslGbl_InputFileList = NULL;
    AslGbl_CurrentLineNumber = 1;
    AslGbl_PreprocessorLineNumber = 1;
    AslGbl_PreprocessorError = FALSE;

    /* These are used to track #if/#else blocks (possibly nested) */

    AslGbl_IfDepth = 0;
    AslGbl_IgnoringThisCodeBlock = FALSE;
    AslGbl_DirectiveStack = NULL;
}