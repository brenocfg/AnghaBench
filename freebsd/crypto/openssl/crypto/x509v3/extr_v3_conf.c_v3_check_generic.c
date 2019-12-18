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
 scalar_t__ ossl_isspace (char const) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int v3_check_generic(const char **value)
{
    int gen_type = 0;
    const char *p = *value;
    if ((strlen(p) >= 4) && strncmp(p, "DER:", 4) == 0) {
        p += 4;
        gen_type = 1;
    } else if ((strlen(p) >= 5) && strncmp(p, "ASN1:", 5) == 0) {
        p += 5;
        gen_type = 2;
    } else
        return 0;

    while (ossl_isspace(*p))
        p++;
    *value = p;
    return gen_type;
}