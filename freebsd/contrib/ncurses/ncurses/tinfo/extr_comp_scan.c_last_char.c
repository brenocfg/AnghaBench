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
 int /*<<< orphan*/  UChar (int) ; 
 int* bufptr ; 
 int /*<<< orphan*/  isspace (int /*<<< orphan*/ ) ; 
 size_t strlen (int*) ; 

__attribute__((used)) static int
last_char(int from_end)
{
    size_t len = strlen(bufptr);
    int result = 0;

    while (len--) {
	if (!isspace(UChar(bufptr[len]))) {
	    if (from_end < (int) len)
		result = bufptr[(int) len - from_end];
	    break;
	}
    }
    return result;
}