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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  rrset_ns ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int ns_sect ;
typedef  int /*<<< orphan*/  ns_rr ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  scalar_t__ ns_class ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  EPROTOTYPE ; 
 int NS_MAXDNAME ; 
 int /*<<< orphan*/  NS_MAXMSG ; 
 int /*<<< orphan*/  abort () ; 
 int do_query (int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_f_rcode ; 
 scalar_t__ ns_makecanon (char const*,char*,int) ; 
 int ns_msg_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_msg_end (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_msg_getflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_name_uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,size_t) ; 
 int /*<<< orphan*/  ns_o_query ; 
 scalar_t__ ns_parserr (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ns_r_noerror ; 
 scalar_t__ ns_rr_class (int /*<<< orphan*/ ) ; 
 char* ns_rr_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ns_rr_rdata (int /*<<< orphan*/ ) ; 
 scalar_t__ ns_rr_type (int /*<<< orphan*/ ) ; 
#define  ns_s_an 129 
 int ns_s_max ; 
#define  ns_s_ns 128 
 int /*<<< orphan*/  ns_samedomain (char const*,char const*) ; 
 int ns_samename (char const*,char const*) ; 
 scalar_t__ ns_t_cname ; 
 scalar_t__ ns_t_dname ; 
 scalar_t__ ns_t_soa ; 
 int /*<<< orphan*/  p_class (scalar_t__) ; 
 int /*<<< orphan*/  p_section (int,int /*<<< orphan*/ ) ; 
 scalar_t__ save_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
get_soa(res_state statp, const char *dname, ns_class class, int opts,
	char *zname, size_t zsize, char *mname, size_t msize,
	rrset_ns *nsrrsp)
{
	char tname[NS_MAXDNAME];
	u_char *resp = NULL;
	int n, i, ancount, nscount;
	ns_sect sect;
	ns_msg msg;
	u_int rcode;

	/*
	 * Find closest enclosing SOA, even if it's for the root zone.
	 */

	/* First canonicalize dname (exactly one unescaped trailing "."). */
	if (ns_makecanon(dname, tname, sizeof tname) < 0)
		goto cleanup;
	dname = tname;

	resp = malloc(NS_MAXMSG);
	if (resp == NULL)
		goto cleanup;

	/* Now grovel the subdomains, hunting for an SOA answer or auth. */
	for (;;) {
		/* Leading or inter-label '.' are skipped here. */
		while (*dname == '.')
			dname++;

		/* Is there an SOA? */
		n = do_query(statp, dname, class, ns_t_soa, resp, &msg);
		if (n < 0) {
			DPRINTF(("get_soa: do_query('%s', %s) failed (%d)",
				 dname, p_class(class), n));
			goto cleanup;
		}
		if (n > 0) {
			DPRINTF(("get_soa: CNAME or DNAME found"));
			sect = ns_s_max, n = 0;
		} else {
			rcode = ns_msg_getflag(msg, ns_f_rcode);
			ancount = ns_msg_count(msg, ns_s_an);
			nscount = ns_msg_count(msg, ns_s_ns);
			if (ancount > 0 && rcode == ns_r_noerror)
				sect = ns_s_an, n = ancount;
			else if (nscount > 0)
				sect = ns_s_ns, n = nscount;
			else
				sect = ns_s_max, n = 0;
		}
		for (i = 0; i < n; i++) {
			const char *t;
			const u_char *rdata;
			ns_rr rr;

			if (ns_parserr(&msg, sect, i, &rr) < 0) {
				DPRINTF(("get_soa: ns_parserr(%s, %d) failed",
					 p_section(sect, ns_o_query), i));
				goto cleanup;
			}
			if (ns_rr_type(rr) == ns_t_cname ||
			    ns_rr_type(rr) == ns_t_dname)
				break;
			if (ns_rr_type(rr) != ns_t_soa ||
			    ns_rr_class(rr) != class)
				continue;
			t = ns_rr_name(rr);
			switch (sect) {
			case ns_s_an:
				if (ns_samedomain(dname, t) == 0) {
					DPRINTF(
				    ("get_soa: ns_samedomain('%s', '%s') == 0",
						dname, t)
						);
					errno = EPROTOTYPE;
					goto cleanup;
				}
				break;
			case ns_s_ns:
				if (ns_samename(dname, t) == 1 ||
				    ns_samedomain(dname, t) == 0) {
					DPRINTF(
		       ("get_soa: ns_samename() || !ns_samedomain('%s', '%s')",
						dname, t)
						);
					errno = EPROTOTYPE;
					goto cleanup;
				}
				break;
			default:
				abort();
			}
			if (strlen(t) + 1 > zsize) {
				DPRINTF(("get_soa: zname(%lu) too small (%lu)",
					 (unsigned long)zsize,
					 (unsigned long)strlen(t) + 1));
				errno = EMSGSIZE;
				goto cleanup;
			}
			strcpy(zname, t);
			rdata = ns_rr_rdata(rr);
			if (ns_name_uncompress(resp, ns_msg_end(msg), rdata,
					       mname, msize) < 0) {
				DPRINTF(("get_soa: ns_name_uncompress failed")
					);
				goto cleanup;
			}
			if (save_ns(statp, &msg, ns_s_ns,
				    zname, class, opts, nsrrsp) < 0) {
				DPRINTF(("get_soa: save_ns failed"));
				goto cleanup;
			}
			free(resp);
			return (0);
		}

		/* If we're out of labels, then not even "." has an SOA! */
		if (*dname == '\0')
			break;

		/* Find label-terminating "."; top of loop will skip it. */
		while (*dname != '.') {
			if (*dname == '\\')
				if (*++dname == '\0') {
					errno = EMSGSIZE;
					goto cleanup;
				}
			dname++;
		}
	}
	DPRINTF(("get_soa: out of labels"));
	errno = EDESTADDRREQ;
 cleanup:
	if (resp != NULL)
		free(resp);
	return (-1);
}