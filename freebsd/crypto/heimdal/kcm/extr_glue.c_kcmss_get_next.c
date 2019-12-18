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
struct kcm_creds {scalar_t__ next; int /*<<< orphan*/  cred; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  scalar_t__ krb5_cc_cursor ;
typedef  int /*<<< orphan*/  kcm_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KCMCACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ KRB5_CC_END ; 
 scalar_t__ krb5_copy_creds_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
kcmss_get_next (krb5_context context,
		krb5_ccache id,
		krb5_cc_cursor *cursor,
		krb5_creds *creds)
{
    krb5_error_code ret;
    kcm_ccache c = KCMCACHE(id);

    KCM_ASSERT_VALID(c);

    ret = krb5_copy_creds_contents(context,
				   &((struct kcm_creds *)cursor)->cred,
				   creds);
    if (ret)
	return ret;

    *cursor = ((struct kcm_creds *)cursor)->next;
    if (*cursor == 0)
	ret = KRB5_CC_END;

    return ret;
}