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
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int min_length_passwd_quality (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static const char *
min_length_passwd_quality_v0 (krb5_context context,
			      krb5_principal principal,
			      krb5_data *pwd)
{
    static char message[1024];
    int ret;

    message[0] = '\0';

    ret = min_length_passwd_quality(context, principal, pwd, NULL,
				    message, sizeof(message));
    if (ret)
	return message;
    return NULL;
}