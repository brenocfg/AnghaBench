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
 int UChar (char const) ; 

__attribute__((used)) static int
skip_csi(const char *cap)
{
    int result = 0;
    if (cap[0] == '\033' && cap[1] == '[')
	result = 2;
    else if (UChar(cap[0]) == 0233)
	result = 1;
    return result;
}