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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  kcm_ccache ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_CC_NOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kcm_ccache_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* kcm_ccache_nextid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

krb5_error_code
kcm_ccache_gen_new(krb5_context context,
		   pid_t pid,
		   uid_t uid,
		   gid_t gid,
		   kcm_ccache *ccache)
{
    krb5_error_code ret;
    char *name;

    name = kcm_ccache_nextid(pid, uid, gid);
    if (name == NULL) {
	return KRB5_CC_NOMEM;
    }

    ret = kcm_ccache_new(context, name, ccache);

    free(name);
    return ret;
}