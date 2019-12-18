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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static int GetBERLen(uint8_t* buf)
{
    if (*buf & 0x80)
    {
        if ((*buf & 0x7F) == 1)
            return buf[1];
        else
            return *(uint16_t*)&buf[1]; // assuming max len is 2
    }
    else
        return buf[0];
}