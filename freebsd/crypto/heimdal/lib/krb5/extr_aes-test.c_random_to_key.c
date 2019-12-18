#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ETYPE_DES3_CBC_SHA1 ; 
 int /*<<< orphan*/  krb5_free_keyblock_contents (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_random_to_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
random_to_key(krb5_context context)
{
    krb5_error_code ret;
    krb5_keyblock key;

    ret = krb5_random_to_key(context,
			     ETYPE_DES3_CBC_SHA1,
			     "\x21\x39\x04\x58\x6A\xBD\x7F"
			     "\x21\x39\x04\x58\x6A\xBD\x7F"
			     "\x21\x39\x04\x58\x6A\xBD\x7F",
			     21,
			     &key);
    if (ret){
	krb5_warn(context, ret, "random_to_key");
	return 1;
    }
    if (key.keyvalue.length != 24)
	return 1;

    if (memcmp(key.keyvalue.data,
	       "\x20\x38\x04\x58\x6b\xbc\x7f\xc7"
	       "\x20\x38\x04\x58\x6b\xbc\x7f\xc7"
	       "\x20\x38\x04\x58\x6b\xbc\x7f\xc7",
	       24) != 0)
	return 1;

    krb5_free_keyblock_contents(context, &key);

    return 0;
}