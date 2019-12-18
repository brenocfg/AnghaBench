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
 char* save_string (char*,char*) ; 
 char* save_tc_char (char*,int) ; 

__attribute__((used)) static char *
save_tc_inequality(char *bufptr, int c1, int c2)
{
    bufptr = save_string(bufptr, "%>");
    bufptr = save_tc_char(bufptr, c1);
    bufptr = save_tc_char(bufptr, c2);
    return bufptr;
}