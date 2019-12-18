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
typedef  scalar_t__ heim_string_t ;

/* Variables and functions */
 scalar_t__ _heim_alloc_object (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _heim_string_object ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 size_t strlen (char const*) ; 

heim_string_t
heim_string_create(const char *string)
{
    size_t len = strlen(string);
    heim_string_t s;

    s = _heim_alloc_object(&_heim_string_object, len + 1);
    if (s)
	memcpy(s, string, len + 1);
    return s;
}