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
typedef  int ossl_ssize_t ;
typedef  int /*<<< orphan*/  linktarget ;

/* Variables and functions */
 scalar_t__ OPENSSL_hexchar2int (unsigned char) ; 
 int OSSL_NELEM (char const**) ; 
 int PATH_MAX ; 
 int add_entry (int,unsigned int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 int readlink (char const*,char*,int) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,scalar_t__) ; 
 int strtoul (char const*,char**,int) ; 
 char const** suffixes ; 

__attribute__((used)) static int handle_symlink(const char *filename, const char *fullpath)
{
    unsigned int hash = 0;
    int i, type, id;
    unsigned char ch;
    char linktarget[PATH_MAX], *endptr;
    ossl_ssize_t n;

    for (i = 0; i < 8; i++) {
        ch = filename[i];
        if (!isxdigit(ch))
            return -1;
        hash <<= 4;
        hash += OPENSSL_hexchar2int(ch);
    }
    if (filename[i++] != '.')
        return -1;
    for (type = OSSL_NELEM(suffixes) - 1; type > 0; type--) {
        const char *suffix = suffixes[type];
        if (strncasecmp(suffix, &filename[i], strlen(suffix)) == 0)
            break;
    }
    i += strlen(suffixes[type]);

    id = strtoul(&filename[i], &endptr, 10);
    if (*endptr != '\0')
        return -1;

    n = readlink(fullpath, linktarget, sizeof(linktarget));
    if (n < 0 || n >= (int)sizeof(linktarget))
        return -1;
    linktarget[n] = 0;

    return add_entry(type, hash, linktarget, NULL, 0, id);
}