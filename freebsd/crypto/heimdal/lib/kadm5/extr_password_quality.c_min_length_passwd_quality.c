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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_principal ;
struct TYPE_3__ {scalar_t__ length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ krb5_config_get_int_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
min_length_passwd_quality (krb5_context context,
			   krb5_principal principal,
			   krb5_data *pwd,
			   const char *opaque,
			   char *message,
			   size_t length)
{
    uint32_t min_length = krb5_config_get_int_default(context, NULL, 6,
						      "password_quality",
						      "min_length",
						      NULL);

    if (pwd->length < min_length) {
	strlcpy(message, "Password too short", length);
	return 1;
    } else
	return 0;
}