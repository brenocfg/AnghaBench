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
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 scalar_t__ PRESENT (char const*) ; 
 int /*<<< orphan*/  set_attributes ; 
 char* strdup (char const*) ; 
 char* tparm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
set_attribute_9(TERMTYPE *tp, int flag)
{
    const char *value;
    char *result;

    value = tparm(set_attributes, 0, 0, 0, 0, 0, 0, 0, 0, flag);
    if (PRESENT(value))
	result = strdup(value);
    else
	result = 0;
    return result;
}