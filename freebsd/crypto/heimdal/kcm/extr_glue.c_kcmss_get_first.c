#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/ * krb5_cc_cursor ;
typedef  TYPE_1__* kcm_ccache ;
struct TYPE_4__ {int /*<<< orphan*/ * creds; } ;

/* Variables and functions */
 TYPE_1__* KCMCACHE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  KRB5_CC_END ; 

__attribute__((used)) static krb5_error_code
kcmss_get_first (krb5_context context,
		 krb5_ccache id,
		 krb5_cc_cursor *cursor)
{
    kcm_ccache c = KCMCACHE(id);

    KCM_ASSERT_VALID(c);

    *cursor = c->creds;

    return (*cursor == NULL) ? KRB5_CC_END : 0;
}