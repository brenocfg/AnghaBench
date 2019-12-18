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
 char CTRL (char) ; 
 char* optarg ; 

__attribute__((used)) static char
arg_to_char(void)
{
    return (char) ((optarg[0] == '^' && optarg[1] != '\0')
		   ? ((optarg[1] == '?') ? '\177' : CTRL(optarg[1]))
		   : optarg[0]);
}