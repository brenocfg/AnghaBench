#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int vno; int /*<<< orphan*/  keyblock; int /*<<< orphan*/  principal; } ;
typedef  TYPE_1__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  entry3 ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  ETYPE_AES256_CTS_HMAC_SHA1_96 ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_generate_random_keyblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_add_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_kt_free_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_kt_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_kt_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
test_memory_keytab(krb5_context context, const char *keytab, const char *keytab2)
{
    krb5_error_code ret;
    krb5_keytab id, id2, id3;
    krb5_keytab_entry entry, entry2, entry3;

    ret = krb5_kt_resolve(context, keytab, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

    memset(&entry, 0, sizeof(entry));
    ret = krb5_parse_name(context, "lha@SU.SE", &entry.principal);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");
    entry.vno = 1;
    ret = krb5_generate_random_keyblock(context,
					ETYPE_AES256_CTS_HMAC_SHA1_96,
					&entry.keyblock);
    if (ret)
	krb5_err(context, 1, ret, "krb5_generate_random_keyblock");

    krb5_kt_add_entry(context, id, &entry);

    ret = krb5_kt_resolve(context, keytab, &id2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

    ret = krb5_kt_get_entry(context, id,
			    entry.principal,
			    0,
			    ETYPE_AES256_CTS_HMAC_SHA1_96,
			    &entry2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_get_entry");
    krb5_kt_free_entry(context, &entry2);

    ret = krb5_kt_close(context, id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_close");

    ret = krb5_kt_get_entry(context, id2,
			    entry.principal,
			    0,
			    ETYPE_AES256_CTS_HMAC_SHA1_96,
			    &entry2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_get_entry");
    krb5_kt_free_entry(context, &entry2);

    ret = krb5_kt_close(context, id2);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_close");


    ret = krb5_kt_resolve(context, keytab2, &id3);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

    memset(&entry3, 0, sizeof(entry3));
    ret = krb5_parse_name(context, "lha3@SU.SE", &entry3.principal);
    if (ret)
	krb5_err(context, 1, ret, "krb5_parse_name");
    entry3.vno = 1;
    ret = krb5_generate_random_keyblock(context,
					ETYPE_AES256_CTS_HMAC_SHA1_96,
					&entry3.keyblock);
    if (ret)
	krb5_err(context, 1, ret, "krb5_generate_random_keyblock");

    krb5_kt_add_entry(context, id3, &entry3);


    ret = krb5_kt_resolve(context, keytab, &id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_resolve");

    ret = krb5_kt_get_entry(context, id,
			    entry.principal,
			    0,
			    ETYPE_AES256_CTS_HMAC_SHA1_96,
			    &entry2);
    if (ret == 0)
	krb5_errx(context, 1, "krb5_kt_get_entry when if should fail");

    krb5_kt_remove_entry(context, id, &entry);

    ret = krb5_kt_close(context, id);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_close");

    krb5_kt_free_entry(context, &entry);

    krb5_kt_remove_entry(context, id3, &entry3);

    ret = krb5_kt_close(context, id3);
    if (ret)
	krb5_err(context, 1, ret, "krb5_kt_close");

    krb5_free_principal(context, entry3.principal);
    krb5_free_keyblock_contents(context, &entry3.keyblock);
}