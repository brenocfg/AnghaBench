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
struct sec_buffer {int /*<<< orphan*/  offset; int /*<<< orphan*/  allocated; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_ret_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_ret_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
ret_sec_buffer(krb5_storage *sp, struct sec_buffer *buf)
{
    krb5_error_code ret;
    CHECK(krb5_ret_uint16(sp, &buf->length), 0);
    CHECK(krb5_ret_uint16(sp, &buf->allocated), 0);
    CHECK(krb5_ret_uint32(sp, &buf->offset), 0);
out:
    return ret;
}