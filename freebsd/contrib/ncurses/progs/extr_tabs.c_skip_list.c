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
 int /*<<< orphan*/  UChar (char) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
skip_list(char *value)
{
    while (*value != '\0' &&
	   (isdigit(UChar(*value)) ||
	    isspace(UChar(*value)) ||
	    strchr("+,", UChar(*value)) != 0)) {
	++value;
    }
    return value;
}