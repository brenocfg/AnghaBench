#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char const* uid_t ;
struct passwd {char const* pw_uid; int /*<<< orphan*/  pw_name; } ;
struct compat_state {int /*<<< orphan*/  template; int /*<<< orphan*/  exclude; } ;
struct TYPE_6__ {int member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ns_src ;
struct TYPE_7__ {void* mdata; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ ns_dtab ;
typedef  enum nss_lookup_type { ____Placeholder_nss_lookup_type } nss_lookup_type ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  NSDB_PASSWD_COMPAT ; 
 int /*<<< orphan*/ * const NSSRC_DNS ; 
#define  NSSRC_NIS 132 
 int NS_NOTFOUND ; 
 int NS_RETURN ; 
#define  NS_SUCCESS 131 
 int NS_UNAVAIL ; 
 int /*<<< orphan*/  __pw_initpwd (struct passwd*) ; 
 int _nsdispatch (void**,TYPE_2__*,int /*<<< orphan*/ ,char*,TYPE_1__ const*,...) ; 
 scalar_t__ compat_is_excluded (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compat_use_template (struct passwd*,int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/ * dns_passwd ; 
 int /*<<< orphan*/ * nis_passwd ; 
 int nitems (TYPE_2__*) ; 
#define  nss_lt_all 130 
#define  nss_lt_id 129 
#define  nss_lt_name 128 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compat_redispatch(struct compat_state *st, enum nss_lookup_type how,
    enum nss_lookup_type lookup_how, const char *name, const char *lookup_name,
    uid_t uid, struct passwd *pwd, char *buffer, size_t bufsize, int *errnop)
{
	static const ns_src compatsrc[] = {
#ifdef YP
		{ NSSRC_NIS, NS_SUCCESS },
#endif
		{ NULL, 0 }
	};
	ns_dtab dtab[] = {
#ifdef YP
		{ NSSRC_NIS, nis_passwd, NULL },
#endif
#ifdef HESIOD
		{ NSSRC_DNS, dns_passwd, NULL },
#endif
		{ NULL, NULL, NULL }
	};
	void		*discard;
	int		 e, i, rv;

	for (i = 0; i < (int)(nitems(dtab) - 1); i++)
		dtab[i].mdata = (void *)lookup_how;
more:
	__pw_initpwd(pwd);
	switch (lookup_how) {
	case nss_lt_all:
		rv = _nsdispatch(&discard, dtab, NSDB_PASSWD_COMPAT,
		    "getpwent_r", compatsrc, pwd, buffer, bufsize,
		    errnop);
		break;
	case nss_lt_id:
		rv = _nsdispatch(&discard, dtab, NSDB_PASSWD_COMPAT,
		    "getpwuid_r", compatsrc, uid, pwd, buffer,
		    bufsize, errnop);
		break;
	case nss_lt_name:
		rv = _nsdispatch(&discard, dtab, NSDB_PASSWD_COMPAT,
		    "getpwnam_r", compatsrc, lookup_name, pwd, buffer,
		    bufsize, errnop);
		break;
	default:
		return (NS_UNAVAIL);
	}
	if (rv != NS_SUCCESS)
		return (rv);
	if (compat_is_excluded(pwd->pw_name, st->exclude)) {
		if (how == nss_lt_all)
			goto more;
		return (NS_NOTFOUND);
	}
	e = compat_use_template(pwd, &st->template, buffer, bufsize);
	if (e != 0) {
		*errnop = e;
		if (e == ERANGE)
			return (NS_RETURN);
		else
			return (NS_UNAVAIL);
	}
	switch (how) {
	case nss_lt_name:
		if (strcmp(name, pwd->pw_name) != 0)
			return (NS_NOTFOUND);
		break;
	case nss_lt_id:
		if (uid != pwd->pw_uid)
			return (NS_NOTFOUND);
		break;
	default:
		break;
	}
	return (NS_SUCCESS);
}