#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {TYPE_3__ saltvalue; int /*<<< orphan*/  salttype; } ;
typedef  TYPE_4__ krb5_salt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_14__ {int /*<<< orphan*/ * data; scalar_t__ length; } ;
struct TYPE_15__ {TYPE_1__ keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_18__ {TYPE_10__* salt; TYPE_2__ key; } ;
struct TYPE_13__ {int /*<<< orphan*/  salt; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ Key ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_10__* calloc (int,int) ; 
 int /*<<< orphan*/  free_Key (TYPE_5__*) ; 
 scalar_t__ krb5_data_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* realloc (TYPE_5__*,size_t) ; 

__attribute__((used)) static krb5_error_code
add_enctype_to_key_set(Key **key_set, size_t *nkeyset,
		       krb5_enctype enctype, krb5_salt *salt)
{
    krb5_error_code ret;
    Key key, *tmp;

    memset(&key, 0, sizeof(key));

    tmp = realloc(*key_set, (*nkeyset + 1) * sizeof((*key_set)[0]));
    if (tmp == NULL)
	return ENOMEM;

    *key_set = tmp;

    key.key.keytype = enctype;
    key.key.keyvalue.length = 0;
    key.key.keyvalue.data = NULL;

    if (salt) {
	key.salt = calloc(1, sizeof(*key.salt));
	if (key.salt == NULL) {
	    free_Key(&key);
	    return ENOMEM;
	}

	key.salt->type = salt->salttype;
	krb5_data_zero (&key.salt->salt);

	ret = krb5_data_copy(&key.salt->salt,
			     salt->saltvalue.data,
			     salt->saltvalue.length);
	if (ret) {
	    free_Key(&key);
	    return ret;
	}
    } else
	key.salt = NULL;

    (*key_set)[*nkeyset] = key;

    *nkeyset += 1;

    return 0;
}