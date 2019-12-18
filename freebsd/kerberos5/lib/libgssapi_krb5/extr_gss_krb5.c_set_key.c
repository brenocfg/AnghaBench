#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ keyvalue; int /*<<< orphan*/  keytype; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ gss_krb5_lucid_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static krb5_error_code
set_key(krb5_keyblock *keyblock, gss_krb5_lucid_key_t *key)
{
    key->type = keyblock->keytype;
    key->length = keyblock->keyvalue.length;
    key->data = malloc(key->length);
    if (key->data == NULL && key->length != 0)
	return ENOMEM;
    memcpy(key->data, keyblock->keyvalue.data, key->length);
    return 0;
}