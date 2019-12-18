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
struct krb5_krbhst_info {int proto; int port; int def_port; char* hostname; struct addrinfo* ai; } ;
struct krb5_krbhst_data {int fallback_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  realm; } ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KD_FALLBACK ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  append_host_hostinfo (struct krb5_krbhst_data*,struct krb5_krbhst_info*) ; 
 int asprintf (char**,char*,char const*,int,...) ; 
 struct krb5_krbhst_info* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  make_hints (struct addrinfo*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static krb5_error_code
fallback_get_hosts(krb5_context context, struct krb5_krbhst_data *kd,
		   const char *serv_string, int port, int proto)
{
    char *host = NULL;
    int ret;
    struct addrinfo *ai;
    struct addrinfo hints;
    char portstr[NI_MAXSERV];

    _krb5_debug(context, 2, "fallback lookup %d for realm %s (service %s)",
		kd->fallback_count, kd->realm, serv_string);

    /*
     * Don't try forever in case the DNS server keep returning us
     * entries (like wildcard entries or the .nu TLD)
     */
    if(kd->fallback_count >= 5) {
	kd->flags |= KD_FALLBACK;
	return 0;
    }

    if(kd->fallback_count == 0)
	ret = asprintf(&host, "%s.%s.", serv_string, kd->realm);
    else
	ret = asprintf(&host, "%s-%d.%s.",
		       serv_string, kd->fallback_count, kd->realm);

    if (ret < 0 || host == NULL)
	return ENOMEM;

    make_hints(&hints, proto);
    snprintf(portstr, sizeof(portstr), "%d", port);
    ret = getaddrinfo(host, portstr, &hints, &ai);
    if (ret) {
	/* no more hosts, so we're done here */
	free(host);
	kd->flags |= KD_FALLBACK;
    } else {
	struct krb5_krbhst_info *hi;
	size_t hostlen = strlen(host);

	hi = calloc(1, sizeof(*hi) + hostlen);
	if(hi == NULL) {
	    free(host);
	    return ENOMEM;
	}

	hi->proto = proto;
	hi->port  = hi->def_port = port;
	hi->ai    = ai;
	memmove(hi->hostname, host, hostlen);
	hi->hostname[hostlen] = '\0';
	free(host);
	append_host_hostinfo(kd, hi);
	kd->fallback_count++;
    }
    return 0;
}