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
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *
keytab_name(const char *name, const char **type, size_t *type_len)
{
    const char *residual;

    residual = strchr(name, ':');

    if (residual == NULL ||
	name[0] == '/'
#ifdef _WIN32
        /* Avoid treating <drive>:<path> as a keytab type
         * specification */
        || name + 1 == residual
#endif
        ) {

        *type = "FILE";
        *type_len = strlen(*type);
        residual = name;
    } else {
        *type = name;
        *type_len = residual - name;
        residual++;
    }

    return residual;
}