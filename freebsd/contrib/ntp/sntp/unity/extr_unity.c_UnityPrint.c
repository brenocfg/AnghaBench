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
typedef  int /*<<< orphan*/  _U_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  UNITY_OUTPUT_CHAR (char const) ; 
 int /*<<< orphan*/  UnityPrintNumberHex (int /*<<< orphan*/ ,int) ; 

void UnityPrint(const char* string)
{
    const char* pch = string;

    if (pch != NULL)
    {
        while (*pch)
        {
            // printable characters plus CR & LF are printed
            if ((*pch <= 126) && (*pch >= 32))
            {
                UNITY_OUTPUT_CHAR(*pch);
            }
            //write escaped carriage returns
            else if (*pch == 13)
            {
                UNITY_OUTPUT_CHAR('\\');
                UNITY_OUTPUT_CHAR('r');
            }
            //write escaped line feeds
            else if (*pch == 10)
            {
                UNITY_OUTPUT_CHAR('\\');
                UNITY_OUTPUT_CHAR('n');
            }
            // unprintable characters are shown as codes
            else
            {
                UNITY_OUTPUT_CHAR('\\');
                UnityPrintNumberHex((_U_UINT)*pch, 2);
            }
            pch++;
        }
    }
}