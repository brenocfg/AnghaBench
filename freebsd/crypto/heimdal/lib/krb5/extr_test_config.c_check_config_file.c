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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  krb5_free_config_files (char**) ; 
 scalar_t__ krb5_get_default_config_files (char***) ; 
 scalar_t__ krb5_prepend_config_files (char*,int /*<<< orphan*/ *,char***) ; 
 scalar_t__ krb5_prepend_config_files_default (char*,char***) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
check_config_file(krb5_context context, char *filelist, char **res, int def)
{
    krb5_error_code ret;
    char **pp;
    int i;

    pp = NULL;

    if (def)
	ret = krb5_prepend_config_files_default(filelist, &pp);
    else
	ret = krb5_prepend_config_files(filelist, NULL, &pp);

    if (ret)
	krb5_err(context, 1, ret, "prepend_config_files");

    for (i = 0; res[i] && pp[i]; i++)
	if (strcmp(pp[i], res[i]) != 0)
	    krb5_errx(context, 1, "'%s' != '%s'", pp[i], res[i]);

    if (res[i] != NULL)
	krb5_errx(context, 1, "pp ended before res list");

    if (def) {
	char **deflist;
	int j;

	ret = krb5_get_default_config_files(&deflist);
	if (ret)
	    krb5_err(context, 1, ret, "get_default_config_files");

	for (j = 0 ; pp[i] && deflist[j]; i++, j++)
	    if (strcmp(pp[i], deflist[j]) != 0)
		krb5_errx(context, 1, "'%s' != '%s'", pp[i], deflist[j]);

	if (deflist[j] != NULL)
	    krb5_errx(context, 1, "pp ended before def list");
	krb5_free_config_files(deflist);
    }

    if (pp[i] != NULL)
	krb5_errx(context, 1, "pp ended after res (and def) list");

    krb5_free_config_files(pp);

    return 0;
}