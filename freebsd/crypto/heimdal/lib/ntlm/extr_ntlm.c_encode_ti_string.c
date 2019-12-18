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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_store_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len_string (int,char*) ; 
 int /*<<< orphan*/  put_string (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int
encode_ti_string(krb5_storage *out, uint16_t type, int ucs2, char *s)
{
    krb5_error_code ret;
    CHECK(krb5_store_uint16(out, type), 0);
    CHECK(krb5_store_uint16(out, len_string(ucs2, s)), 0);
    CHECK(put_string(out, ucs2, s), 0);
out:
    return ret;
}