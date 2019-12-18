#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {TYPE_1__ saltvalue; int /*<<< orphan*/  salttype; } ;
struct pa_info_data {int /*<<< orphan*/ * s2kparams; TYPE_2__ salt; int /*<<< orphan*/  etype; } ;
typedef  int /*<<< orphan*/  krb5_salttype ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_copy_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_free_salt (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static krb5_error_code
set_paid(struct pa_info_data *paid, krb5_context context,
	 krb5_enctype etype,
	 krb5_salttype salttype, void *salt_string, size_t salt_len,
	 krb5_data *s2kparams)
{
    paid->etype = etype;
    paid->salt.salttype = salttype;
    paid->salt.saltvalue.data = malloc(salt_len + 1);
    if (paid->salt.saltvalue.data == NULL) {
	krb5_clear_error_message(context);
	return ENOMEM;
    }
    memcpy(paid->salt.saltvalue.data, salt_string, salt_len);
    ((char *)paid->salt.saltvalue.data)[salt_len] = '\0';
    paid->salt.saltvalue.length = salt_len;
    if (s2kparams) {
	krb5_error_code ret;

	ret = krb5_copy_data(context, s2kparams, &paid->s2kparams);
	if (ret) {
	    krb5_clear_error_message(context);
	    krb5_free_salt(context, paid->salt);
	    return ret;
	}
    } else
	paid->s2kparams = NULL;

    return 0;
}