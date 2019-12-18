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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_ccache ;

/* Variables and functions */
 scalar_t__ kcm_ccache_alloc (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_retain_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

krb5_error_code
kcm_ccache_new(krb5_context context,
	       const char *name,
	       kcm_ccache *ccache)
{
    krb5_error_code ret;

    ret = kcm_ccache_alloc(context, name, ccache);
    if (ret == 0) {
	/*
	 * one reference is held by the linked list,
	 * one by the caller
	 */
	kcm_retain_ccache(context, *ccache);
    }

    return ret;
}