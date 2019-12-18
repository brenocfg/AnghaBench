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
typedef  long _U_UINT ;
typedef  long _U_SINT ;

/* Variables and functions */
 int UNITY_LONG_WIDTH ; 
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char) ; 

void UnityPrintNumber(const _U_SINT number_to_print)
{
    _U_SINT divisor = 1;
    _U_SINT next_divisor;
    _U_UINT number;

    if (number_to_print == (1l << (UNITY_LONG_WIDTH-1)))
    {
        //The largest representable negative number
        UNITY_OUTPUT_CHAR('-');
        number = (1ul << (UNITY_LONG_WIDTH-1));
    }
    else if (number_to_print < 0)
    {
        //Some other negative number
        UNITY_OUTPUT_CHAR('-');
        number = (_U_UINT)(-number_to_print);
    }
    else
    {
        //Positive number
        number = (_U_UINT)number_to_print;
    }

    // figure out initial divisor
    while (number / divisor > 9)
    {
        next_divisor = divisor * 10;
        if (next_divisor > divisor)
            divisor = next_divisor;
        else
            break;
    }

    // now mod and print, then divide divisor
    do
    {
        UNITY_OUTPUT_CHAR((char)('0' + (number / divisor % 10)));
        divisor /= 10;
    }
    while (divisor > 0);
}