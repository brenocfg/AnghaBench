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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  PTYPE ;

/* Variables and functions */
 int ENOMEM ; 
 char* getenv (char*) ; 
 scalar_t__ issuid () ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
_expand_temp_folder(krb5_context context, PTYPE param, const char *postfix, char **ret)
{
    const char *p = NULL;

    if (issuid())
	p = getenv("TEMP");
    if (p)
	*ret = strdup(p);
    else
	*ret = strdup("/tmp");
    if (*ret == NULL)
	return ENOMEM;
    return 0;
}