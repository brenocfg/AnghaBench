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
typedef  int _U_UINT ;
typedef  scalar_t__ _U_SINT ;
typedef  int UNITY_DISPLAY_STYLE_T ;

/* Variables and functions */
 int const UNITY_DISPLAY_RANGE_INT ; 
 int const UNITY_DISPLAY_RANGE_UINT ; 
 int /*<<< orphan*/  UnityPrintNumber (scalar_t__ const) ; 
 int /*<<< orphan*/  UnityPrintNumberHex (int,char) ; 
 int /*<<< orphan*/  UnityPrintNumberUnsigned (int) ; 
 int* UnitySizeMask ; 

void UnityPrintNumberByStyle(const _U_SINT number, const UNITY_DISPLAY_STYLE_T style)
{
    if ((style & UNITY_DISPLAY_RANGE_INT) == UNITY_DISPLAY_RANGE_INT)
    {
        UnityPrintNumber(number);
    }
    else if ((style & UNITY_DISPLAY_RANGE_UINT) == UNITY_DISPLAY_RANGE_UINT)
    {
        UnityPrintNumberUnsigned(  (_U_UINT)number  &  UnitySizeMask[((_U_UINT)style & (_U_UINT)0x0F) - 1]  );
    }
    else
    {
        UnityPrintNumberHex((_U_UINT)number, (char)((style & 0x000F) << 1));
    }
}