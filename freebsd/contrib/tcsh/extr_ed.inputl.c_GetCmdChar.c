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
typedef  size_t wint_t ;
typedef  size_t Char ;

/* Variables and functions */
 size_t CHAR ; 
 int* CurrentKeyMap ; 
 int F_INSERT ; 
 size_t NT_NUM_KEYS ; 

int
GetCmdChar(Char ch)
{
#ifndef WINNT_NATIVE // We use more than 256 for various extended keys 
    wint_t c = ch & CHAR;
#else
    wint_t c = ch;
#endif
    return c < NT_NUM_KEYS ? CurrentKeyMap[c] : F_INSERT;
}