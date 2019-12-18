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
 char* xestring ; 
 char* xstring ; 

__attribute__((used)) static void
xaddchar(int c)
{
    if (xestring == xstring)
	*xstring = '\0';
    else
	*xstring++ = (char) c;
}