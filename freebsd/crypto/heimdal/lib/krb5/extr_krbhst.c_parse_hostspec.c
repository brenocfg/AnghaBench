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
struct krb5_krbhst_info {char* hostname; int port; int def_port; void* proto; } ;
struct krb5_krbhst_data {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 void* KRB5_KRBHST_HTTP ; 
 void* KRB5_KRBHST_TCP ; 
 struct krb5_krbhst_info* calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  free (struct krb5_krbhst_info*) ; 
 int /*<<< orphan*/  krb5_getportbyname (int /*<<< orphan*/ ,char*,char*,int) ; 
 void* krbhst_get_default_proto (struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strlwr (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ strsep_copy (char const**,char*,char*,scalar_t__) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct krb5_krbhst_info*
parse_hostspec(krb5_context context, struct krb5_krbhst_data *kd,
	       const char *spec, int def_port, int port)
{
    const char *p = spec, *q;
    struct krb5_krbhst_info *hi;

    hi = calloc(1, sizeof(*hi) + strlen(spec));
    if(hi == NULL)
	return NULL;

    hi->proto = krbhst_get_default_proto(kd);

    if(strncmp(p, "http://", 7) == 0){
	hi->proto = KRB5_KRBHST_HTTP;
	p += 7;
    } else if(strncmp(p, "http/", 5) == 0) {
	hi->proto = KRB5_KRBHST_HTTP;
	p += 5;
	def_port = ntohs(krb5_getportbyname (context, "http", "tcp", 80));
    }else if(strncmp(p, "tcp/", 4) == 0){
	hi->proto = KRB5_KRBHST_TCP;
	p += 4;
    } else if(strncmp(p, "udp/", 4) == 0) {
	p += 4;
    }

    if (p[0] == '[' && (q = strchr(p, ']')) != NULL) {
	/* if address looks like [foo:bar] or [foo:bar]: its a ipv6
	   adress, strip of [] */
	memcpy(hi->hostname, &p[1], q - p - 1);
	hi->hostname[q - p - 1] = '\0';
	p = q + 1;
	/* get trailing : */
	if (p[0] == ':')
	    p++;
    } else if(strsep_copy(&p, ":", hi->hostname, strlen(spec) + 1) < 0) {
	/* copy everything before : */
	free(hi);
	return NULL;
    }
    /* get rid of trailing /, and convert to lower case */
    hi->hostname[strcspn(hi->hostname, "/")] = '\0';
    strlwr(hi->hostname);

    hi->port = hi->def_port = def_port;
    if(p != NULL && p[0]) {
	char *end;
	hi->port = strtol(p, &end, 0);
	if(end == p) {
	    free(hi);
	    return NULL;
	}
    }
    if (port)
	hi->port = port;
    return hi;
}