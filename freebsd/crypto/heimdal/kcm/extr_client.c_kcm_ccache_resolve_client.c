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
typedef  int /*<<< orphan*/  kcm_operation ;
typedef  int /*<<< orphan*/  kcm_client ;
typedef  int /*<<< orphan*/  kcm_ccache ;

/* Variables and functions */
 scalar_t__ KRB5_FCC_NOFILE ; 
 scalar_t__ kcm_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kcm_ccache_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcm_log (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_release_ccache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_err_text (int /*<<< orphan*/ ,scalar_t__) ; 

krb5_error_code
kcm_ccache_resolve_client(krb5_context context,
			  kcm_client *client,
			  kcm_operation opcode,
			  const char *name,
			  kcm_ccache *ccache)
{
    krb5_error_code ret;

    ret = kcm_ccache_resolve(context, name, ccache);
    if (ret) {
	kcm_log(1, "Failed to resolve cache %s: %s",
		name, krb5_get_err_text(context, ret));
	return ret;
    }

    ret = kcm_access(context, client, opcode, *ccache);
    if (ret) {
	ret = KRB5_FCC_NOFILE; /* don't disclose */
	kcm_release_ccache(context, *ccache);
    }

    return ret;
}