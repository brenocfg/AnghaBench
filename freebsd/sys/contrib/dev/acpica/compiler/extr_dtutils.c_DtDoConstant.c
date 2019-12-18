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
typedef  int /*<<< orphan*/  UINT64 ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiUtImplicitStrtoul64 (char*) ; 

UINT64
DtDoConstant (
    char                    *String)
{
    UINT64                  ConvertedInteger;


    /*
     * TBD: The ImplicitStrtoul64 function does not report overflow
     * conditions. The input string is simply truncated. If it is
     * desired to report overflow to the table compiler, this should
     * somehow be added here. Note: integers that are prefixed with 0x
     * or not are both hex integers.
     */
    ConvertedInteger = AcpiUtImplicitStrtoul64 (String);
    return (ConvertedInteger);
}