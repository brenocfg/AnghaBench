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
 int FALSE ; 
 int TRUE ; 
 char* bufptr ; 
 int feof (scalar_t__) ; 
 scalar_t__ yyin ; 

__attribute__((used)) static bool
end_of_stream(void)
/* are we at end of input? */
{
    return ((yyin ? feof(yyin) : (bufptr && *bufptr == '\0'))
	    ? TRUE : FALSE);
}