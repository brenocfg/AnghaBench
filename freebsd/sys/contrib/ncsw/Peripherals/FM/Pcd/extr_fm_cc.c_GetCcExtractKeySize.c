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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static void GetCcExtractKeySize(uint8_t parseCodeRealSize,
                                uint8_t *parseCodeCcSize)
{
    if ((parseCodeRealSize > 0) && (parseCodeRealSize < 2))
        *parseCodeCcSize = 1;
    else
        if (parseCodeRealSize == 2)
            *parseCodeCcSize = 2;
        else
            if ((parseCodeRealSize > 2) && (parseCodeRealSize <= 4))
                *parseCodeCcSize = 4;
            else
                if ((parseCodeRealSize > 4) && (parseCodeRealSize <= 8))
                    *parseCodeCcSize = 8;
                else
                    if ((parseCodeRealSize > 8) && (parseCodeRealSize <= 16))
                        *parseCodeCcSize = 16;
                    else
                        if ((parseCodeRealSize > 16)
                                && (parseCodeRealSize <= 24))
                            *parseCodeCcSize = 24;
                        else
                            if ((parseCodeRealSize > 24)
                                    && (parseCodeRealSize <= 32))
                                *parseCodeCcSize = 32;
                            else
                                if ((parseCodeRealSize > 32)
                                        && (parseCodeRealSize <= 40))
                                    *parseCodeCcSize = 40;
                                else
                                    if ((parseCodeRealSize > 40)
                                            && (parseCodeRealSize <= 48))
                                        *parseCodeCcSize = 48;
                                    else
                                        if ((parseCodeRealSize > 48)
                                                && (parseCodeRealSize <= 56))
                                            *parseCodeCcSize = 56;
                                        else
                                            *parseCodeCcSize = 0;
}