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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 size_t ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_WARNING_AS_ERROR ; 
 size_t ASL_WARNING ; 
 size_t ASL_WARNING2 ; 
 size_t ASL_WARNING3 ; 
 int /*<<< orphan*/  AslError (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__* AslGbl_ExceptionCount ; 
 int /*<<< orphan*/  AslGbl_IgnoreErrors ; 
 scalar_t__ AslGbl_WarningsAsErrors ; 

ACPI_STATUS
AslCheckForErrorExit (
    void)
{

    /*
     * Return non-zero exit code if there have been errors, unless the
     * global ignore error flag has been set
     */
    if (!AslGbl_IgnoreErrors)
    {
        if (AslGbl_ExceptionCount[ASL_ERROR] > 0)
        {
            return (AE_ERROR);
        }

        /* Optionally treat warnings as errors */

        if (AslGbl_WarningsAsErrors)
        {
            if ((AslGbl_ExceptionCount[ASL_WARNING] > 0)  ||
                (AslGbl_ExceptionCount[ASL_WARNING2] > 0) ||
                (AslGbl_ExceptionCount[ASL_WARNING3] > 0))
            {
                AslError (ASL_ERROR, ASL_MSG_WARNING_AS_ERROR, NULL,
                    "(reporting warnings as errors)");
                return (AE_ERROR);
            }
        }
    }

    return (AE_OK);
}