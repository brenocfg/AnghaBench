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
 int /*<<< orphan*/  stricmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
is_valid_plugin_filename(const char * n)
{
    if (n[0] == '.' && (n[1] == '\0' || (n[1] == '.' && n[2] == '\0')))
        return 0;

#ifdef _WIN32
    /* On Windows, we only attempt to load .dll files as plug-ins. */
    {
        const char * ext;

        ext = strrchr(n, '.');
        if (ext == NULL)
            return 0;

        return !stricmp(ext, ".dll");
    }
#else
    return 1;
#endif
}