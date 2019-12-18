#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_cc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_get_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
test_cc_config(krb5_context context)
{
    krb5_error_code ret;
    krb5_principal p;
    krb5_ccache id;
    unsigned int i;

    ret = krb5_cc_new_unique(context, "MEMORY", "bar", &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_new_unique");

    ret = krb5_parse_name(context, "lha@SU.SE", &p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");

    ret = krb5_cc_initialize(context, id, p);
    if (ret)
	krb5_err(context, 1, ret, "krb5_cc_initialize");

    for (i = 0; i < 1000; i++) {
	krb5_data data, data2;
	const char *name = "foo";
	krb5_principal p1 = NULL;

	if (i & 1)
	    p1 = p;

	data.data = rk_UNCONST(name);
	data.length = strlen(name);

	ret = krb5_cc_set_config(context, id, p1, "FriendlyName", &data);
	if (ret)
	    krb5_errx(context, 1, "krb5_cc_set_config: add");

	ret = krb5_cc_get_config(context, id, p1, "FriendlyName", &data2);
	if (ret)
	    krb5_errx(context, 1, "krb5_cc_get_config: first");
	krb5_data_free(&data2);

	ret = krb5_cc_set_config(context, id, p1, "FriendlyName", &data);
	if (ret)
	    krb5_errx(context, 1, "krb5_cc_set_config: add -second");

	ret = krb5_cc_get_config(context, id, p1, "FriendlyName", &data2);
	if (ret)
	    krb5_errx(context, 1, "krb5_cc_get_config: second");
	krb5_data_free(&data2);

	ret = krb5_cc_set_config(context, id, p1, "FriendlyName", NULL);
	if (ret)
	    krb5_errx(context, 1, "krb5_cc_set_config: delete");

	ret = krb5_cc_get_config(context, id, p1, "FriendlyName", &data2);
	if (ret == 0)
	    krb5_errx(context, 1, "krb5_cc_get_config: non-existant");
    }

    krb5_cc_destroy(context, id);
    krb5_free_principal(context, p);
}