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
 int strlen (char const*) ; 

__attribute__((used)) static int ends_with_dirsep(const char *uri)
{
    if (*uri != '\0')
        uri += strlen(uri) - 1;
#if defined __VMS
    if (*uri == ']' || *uri == '>' || *uri == ':')
        return 1;
#elif defined _WIN32
    if (*uri == '\\')
        return 1;
#endif
    return *uri == '/';
}