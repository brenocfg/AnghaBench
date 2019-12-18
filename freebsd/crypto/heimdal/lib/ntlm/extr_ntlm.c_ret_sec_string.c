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
struct sec_buffer {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  krb5_storage_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static krb5_error_code
ret_sec_string(krb5_storage *sp, int ucs2, struct sec_buffer *desc, char **s)
{
    krb5_error_code ret = 0;
    CHECK(krb5_storage_seek(sp, desc->offset, SEEK_SET), desc->offset);
    CHECK(ret_string(sp, ucs2, desc->length, s), 0);
 out:
    return ret;
}