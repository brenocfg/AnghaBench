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
 char* malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 size_t strlen (char const*) ; 

char* _glfw_strdup(const char* source)
{
    const size_t length = strlen(source);
    char* result = malloc(length + 1);
    memcpy(result, source, length);
    result[length] = 0;
    return result;
}