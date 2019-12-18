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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ETYPE_NULL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_config_free_strings (char**) ; 
 char** krb5_config_get_strings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_enctype_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_string_to_enctype (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static krb5_error_code
set_etypes (krb5_context context,
	    const char *name,
	    krb5_enctype **ret_enctypes)
{
    char **etypes_str;
    krb5_enctype *etypes = NULL;

    etypes_str = krb5_config_get_strings(context, NULL, "libdefaults",
					 name, NULL);
    if(etypes_str){
	int i, j, k;
	for(i = 0; etypes_str[i]; i++);
	etypes = malloc((i+1) * sizeof(*etypes));
	if (etypes == NULL) {
	    krb5_config_free_strings (etypes_str);
	    krb5_set_error_message (context, ENOMEM, N_("malloc: out of memory", ""));
	    return ENOMEM;
	}
	for(j = 0, k = 0; j < i; j++) {
	    krb5_enctype e;
	    if(krb5_string_to_enctype(context, etypes_str[j], &e) != 0)
		continue;
	    if (krb5_enctype_valid(context, e) != 0)
		continue;
	    etypes[k++] = e;
	}
	etypes[k] = ETYPE_NULL;
	krb5_config_free_strings(etypes_str);
    }
    *ret_enctypes = etypes;
    return 0;
}