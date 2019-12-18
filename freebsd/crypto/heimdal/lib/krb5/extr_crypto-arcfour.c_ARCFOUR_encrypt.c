#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct _krb5_key_data {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ARCFOUR_subdecrypt (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,void*) ; 
 int /*<<< orphan*/  ARCFOUR_subencrypt (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,unsigned int,void*) ; 
 int /*<<< orphan*/  _krb5_usage2arcfour (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static krb5_error_code
ARCFOUR_encrypt(krb5_context context,
		struct _krb5_key_data *key,
		void *data,
		size_t len,
		krb5_boolean encryptp,
		int usage,
		void *ivec)
{
    krb5_error_code ret;
    unsigned keyusage = usage;

    if((ret = _krb5_usage2arcfour (context, &keyusage)) != 0)
	return ret;

    if (encryptp)
	return ARCFOUR_subencrypt (context, key, data, len, keyusage, ivec);
    else
	return ARCFOUR_subdecrypt (context, key, data, len, keyusage, ivec);
}