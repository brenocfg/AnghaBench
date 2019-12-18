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
struct kafs_token {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _kafs_foldup (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_appdefault_string (int /*<<< orphan*/ ,char*,char*,char*,char*,char**) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  v5_to_kt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kafs_token*,int) ; 

__attribute__((used)) static krb5_error_code
v5_convert(krb5_context context, krb5_ccache id,
	   krb5_creds *cred, uid_t uid,
	   const char *cell,
	   struct kafs_token *kt)
{
    krb5_error_code ret;
    char *c, *val;

    c = strdup(cell);
    if (c == NULL)
	return ENOMEM;
    _kafs_foldup(c, c);
    krb5_appdefault_string (context, "libkafs",
			    c,
			    "afs-use-524", "2b", &val);
    free(c);

    if (strcasecmp(val, "local") == 0 ||
	strcasecmp(val, "2b") == 0)
	ret = v5_to_kt(cred, uid, kt, 1);
    else
	ret = v5_to_kt(cred, uid, kt, 0);

    free(val);
    return ret;
}