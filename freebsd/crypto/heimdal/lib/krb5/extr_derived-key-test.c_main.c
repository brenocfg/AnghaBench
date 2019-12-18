#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct testcase {scalar_t__ enctype; unsigned char* key; int* res; int /*<<< orphan*/  constant_len; int /*<<< orphan*/  constant; } ;
struct TYPE_6__ {int length; unsigned char* data; } ;
struct TYPE_7__ {TYPE_1__ keyvalue; int /*<<< orphan*/  keytype; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  KEYTYPE_DES3 ; 
 int MAXSIZE ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 scalar_t__ krb5_derive_key (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct testcase* tests ; 

int
main(int argc, char **argv)
{
    struct testcase *t;
    krb5_context context;
    krb5_error_code ret;
    int val = 0;

    ret = krb5_init_context (&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    for (t = tests; t->enctype != 0; ++t) {
	krb5_keyblock key;
	krb5_keyblock *dkey;

	key.keytype = KEYTYPE_DES3;
	key.keyvalue.length = MAXSIZE;
	key.keyvalue.data   = t->key;

	ret = krb5_derive_key(context, &key, t->enctype, t->constant,
			      t->constant_len, &dkey);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_derive_key");
	if (memcmp (dkey->keyvalue.data, t->res, dkey->keyvalue.length) != 0) {
	    const unsigned char *p = dkey->keyvalue.data;
	    int i;

	    printf ("derive_key failed\n");
	    printf ("should be: ");
	    for (i = 0; i < dkey->keyvalue.length; ++i)
		printf ("%02x", t->res[i]);
	    printf ("\nresult was: ");
	    for (i = 0; i < dkey->keyvalue.length; ++i)
		printf ("%02x", p[i]);
	    printf ("\n");
	    val = 1;
	}
	krb5_free_keyblock(context, dkey);
    }
    krb5_free_context(context);

    return val;
}