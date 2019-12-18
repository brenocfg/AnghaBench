#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ saltvalue; } ;
typedef  TYPE_2__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_9__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_string_to_key_derived (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static krb5_error_code
DES3_string_to_key_derived(krb5_context context,
			   krb5_enctype enctype,
			   krb5_data password,
			   krb5_salt salt,
			   krb5_data opaque,
			   krb5_keyblock *key)
{
    krb5_error_code ret;
    size_t len = password.length + salt.saltvalue.length;
    char *s;

    s = malloc(len);
    if(len != 0 && s == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    memcpy(s, password.data, password.length);
    memcpy(s + password.length, salt.saltvalue.data, salt.saltvalue.length);
    ret = krb5_string_to_key_derived(context,
				     s,
				     len,
				     enctype,
				     key);
    memset(s, 0, len);
    free(s);
    return ret;
}