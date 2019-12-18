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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 size_t LAST_FRAGMENT ; 
 int krb5_ret_uint32 (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  read_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
collect_framents(krb5_storage *sp, krb5_storage *msg)
{
    krb5_error_code ret;
    uint32_t len;
    int last_fragment;
    size_t total_len = 0;

    do {
	ret = krb5_ret_uint32(sp, &len);
	if (ret)
	    return ret;

	last_fragment = (len & LAST_FRAGMENT);
	len &= ~LAST_FRAGMENT;

	CHECK(read_data(sp, msg, len));
	total_len += len;

    } while(!last_fragment || total_len == 0);

    return 0;
}