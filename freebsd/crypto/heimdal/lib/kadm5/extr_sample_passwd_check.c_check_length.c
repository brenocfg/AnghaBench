#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_3__ {int length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int krb5_config_get_int_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 

const char*
check_length(krb5_context context,
             krb5_principal prinipal,
             krb5_data *password)
{
    int min_length = krb5_config_get_int_default(context, NULL, 6,
						 "password_quality",
						 "min_length",
						 NULL);
    if(password->length < min_length)
	return "Password too short";
    return NULL;
}