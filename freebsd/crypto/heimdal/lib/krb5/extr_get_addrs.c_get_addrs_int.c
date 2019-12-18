#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ krb5_addresses ;

/* Variables and functions */
 int EXTRA_ADDRESSES ; 
 int SCAN_INTERFACES ; 
 scalar_t__ find_all_addresses (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gethostname_fallback (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_append_addresses (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_get_extra_addresses (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static krb5_error_code
get_addrs_int (krb5_context context, krb5_addresses *res, int flags)
{
    krb5_error_code ret = -1;

    res->len = 0;
    res->val = NULL;

    if (flags & SCAN_INTERFACES) {
	ret = find_all_addresses (context, res, flags);
	if(ret || res->len == 0)
	    ret = gethostname_fallback (context, res);
    } else {
	ret = 0;
    }

    if(ret == 0 && (flags & EXTRA_ADDRESSES)) {
	krb5_addresses a;
	/* append user specified addresses */
	ret = krb5_get_extra_addresses(context, &a);
	if(ret) {
	    krb5_free_addresses(context, res);
	    return ret;
	}
	ret = krb5_append_addresses(context, res, &a);
	if(ret) {
	    krb5_free_addresses(context, res);
	    return ret;
	}
	krb5_free_addresses(context, &a);
    }
    if(res->len == 0) {
	free(res->val);
	res->val = NULL;
    }
    return ret;
}