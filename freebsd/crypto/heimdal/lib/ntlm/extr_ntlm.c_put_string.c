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
struct ntlm_buf {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ascii2ucs2le (char const*,int /*<<< orphan*/ ,struct ntlm_buf*) ; 
 int /*<<< orphan*/  heim_ntlm_free_buf (struct ntlm_buf*) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_UNCONST (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static krb5_error_code
put_string(krb5_storage *sp, int ucs2, const char *s)
{
    krb5_error_code ret;
    struct ntlm_buf buf;

    if (ucs2) {
	ret = ascii2ucs2le(s, 0, &buf);
	if (ret)
	    return ret;
    } else {
	buf.data = rk_UNCONST(s);
	buf.length = strlen(s);
    }

    CHECK(krb5_storage_write(sp, buf.data, buf.length), buf.length);
    if (ucs2)
	heim_ntlm_free_buf(&buf);
    ret = 0;
out:
    return ret;
}