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
typedef  int /*<<< orphan*/  krb5_krbhst_info ;
typedef  int /*<<< orphan*/  krb5_krbhst_handle ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  host ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ KRB5_KDC_UNREACH ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  krb5_free_krbhst (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_krbhst_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_krbhst_init (int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_krbhst_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_krbhst_next_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  krb5_krbhst_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static krb5_error_code
gethostlist(krb5_context context, const char *realm,
	    unsigned int type, char ***hostlist)
{
    krb5_error_code ret;
    int nhost = 0;
    krb5_krbhst_handle handle;
    char host[MAXHOSTNAMELEN];
    krb5_krbhst_info *hostinfo;

    ret = krb5_krbhst_init(context, realm, type, &handle);
    if (ret)
	return ret;

    while(krb5_krbhst_next(context, handle, &hostinfo) == 0)
	nhost++;
    if(nhost == 0) {
	krb5_set_error_message(context, KRB5_KDC_UNREACH,
			       N_("No KDC found for realm %s", ""), realm);
	return KRB5_KDC_UNREACH;
    }
    *hostlist = calloc(nhost + 1, sizeof(**hostlist));
    if(*hostlist == NULL) {
	krb5_krbhst_free(context, handle);
	return ENOMEM;
    }

    krb5_krbhst_reset(context, handle);
    nhost = 0;
    while(krb5_krbhst_next_as_string(context, handle,
				     host, sizeof(host)) == 0) {
	if(((*hostlist)[nhost++] = strdup(host)) == NULL) {
	    krb5_free_krbhst(context, *hostlist);
	    krb5_krbhst_free(context, handle);
	    return ENOMEM;
	}
    }
    (*hostlist)[nhost] = NULL;
    krb5_krbhst_free(context, handle);
    return 0;
}