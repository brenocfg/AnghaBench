#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_14__ {TYPE_1__ saltvalue; int /*<<< orphan*/  salttype; } ;
typedef  TYPE_4__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_16__ {int /*<<< orphan*/  keytype; } ;
struct TYPE_15__ {TYPE_7__ key; TYPE_3__* salt; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_2__ salt; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ Key ;

/* Variables and functions */
 int /*<<< orphan*/  hdb_free_keys (int /*<<< orphan*/ ,size_t,TYPE_5__*) ; 
 scalar_t__ hdb_generate_key_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_string_to_key_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_4__,TYPE_7__*) ; 

krb5_error_code
hdb_generate_key_set_password(krb5_context context,
			      krb5_principal principal,
			      const char *password,
			      Key **keys, size_t *num_keys)
{
    krb5_error_code ret;
    size_t i;

    ret = hdb_generate_key_set(context, principal,
				keys, num_keys, 0);
    if (ret)
	return ret;

    for (i = 0; i < (*num_keys); i++) {
	krb5_salt salt;

	salt.salttype = (*keys)[i].salt->type;
	salt.saltvalue.length = (*keys)[i].salt->salt.length;
	salt.saltvalue.data = (*keys)[i].salt->salt.data;

	ret = krb5_string_to_key_salt (context,
				       (*keys)[i].key.keytype,
				       password,
				       salt,
				       &(*keys)[i].key);

	if(ret)
	    break;
    }

    if(ret) {
	hdb_free_keys (context, *num_keys, *keys);
	return ret;
    }
    return ret;
}