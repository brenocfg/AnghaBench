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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_config_section ;
typedef  int /*<<< orphan*/  krb5_config_binding ;

/* Variables and functions */
 void const* _krb5_config_vget_next (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ) ; 

const void *
_krb5_config_vget (krb5_context context,
		   const krb5_config_section *c,
		   int type,
		   va_list args)
{
    const krb5_config_binding *foo = NULL;

    return _krb5_config_vget_next (context, c, &foo, type, args);
}