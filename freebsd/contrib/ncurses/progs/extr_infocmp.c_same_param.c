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
 int /*<<< orphan*/  UChar (char const) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool
same_param(const char *table, const char *param, size_t length)
{
    bool result = FALSE;
    if (strncmp(table, param, length) == 0) {
	result = !isdigit(UChar(param[length]));
    }
    return result;
}