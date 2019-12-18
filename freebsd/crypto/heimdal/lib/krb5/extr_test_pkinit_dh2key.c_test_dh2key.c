#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_14__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ heim_octet_string ;

/* Variables and functions */
 scalar_t__ _krb5_pk_octetstring2key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_dh2key(int i,
	    krb5_context context,
	    const heim_octet_string *dh,
	    const heim_octet_string *c_n,
	    const heim_octet_string *k_n,
	    krb5_enctype etype,
	    const heim_octet_string *result)
{
    krb5_error_code ret;
    krb5_keyblock key;

    ret = _krb5_pk_octetstring2key(context,
				   etype,
				   dh->data, dh->length,
				   c_n,
				   k_n,
				   &key);
    if (ret != 0)
	krb5_err(context, 1, ret, "_krb5_pk_octetstring2key: %d", i);

    if (key.keyvalue.length != result->length ||
	memcmp(key.keyvalue.data, result->data, result->length) != 0)
	krb5_errx(context, 1, "resulting key wrong: %d", i);

    krb5_free_keyblock_contents(context, &key);
}