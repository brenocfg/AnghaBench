#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ time_t ;
struct sshauthopt {scalar_t__ valid_before; int /*<<< orphan*/ * required_from_host_cert; int /*<<< orphan*/ * required_from_host_keys; scalar_t__ cert_authority; int /*<<< orphan*/ * cert_principals; } ;
struct ssh {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_name; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  use_dns; } ;

/* Variables and functions */
 int addr_match_cidr_list (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auth_debug_add (char*,char const*,...) ; 
 char* auth_get_canonical_hostname (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auth_log_authopts (char const*,struct sshauthopt*,int) ; 
 int /*<<< orphan*/  debug (char*,char const*,...) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  format_absolute_time (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  logit (char*,char const*,int /*<<< orphan*/ ,char const*,...) ; 
 int match_host_and_ip (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__ options ; 
 char* ssh_remote_ipaddr (struct ssh*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
auth_authorise_keyopts(struct ssh *ssh, struct passwd *pw,
    struct sshauthopt *opts, int allow_cert_authority, const char *loc)
{
	const char *remote_ip = ssh_remote_ipaddr(ssh);
	const char *remote_host = auth_get_canonical_hostname(ssh,
	    options.use_dns);
	time_t now = time(NULL);
	char buf[64];

	/*
	 * Check keys/principals file expiry time.
	 * NB. validity interval in certificate is handled elsewhere.
	 */
	if (opts->valid_before && now > 0 &&
	    opts->valid_before < (uint64_t)now) {
		format_absolute_time(opts->valid_before, buf, sizeof(buf));
		debug("%s: entry expired at %s", loc, buf);
		auth_debug_add("%s: entry expired at %s", loc, buf);
		return -1;
	}
	/* Consistency checks */
	if (opts->cert_principals != NULL && !opts->cert_authority) {
		debug("%s: principals on non-CA key", loc);
		auth_debug_add("%s: principals on non-CA key", loc);
		/* deny access */
		return -1;
	}
	/* cert-authority flag isn't valid in authorized_principals files */
	if (!allow_cert_authority && opts->cert_authority) {
		debug("%s: cert-authority flag invalid here", loc);
		auth_debug_add("%s: cert-authority flag invalid here", loc);
		/* deny access */
		return -1;
	}

	/* Perform from= checks */
	if (opts->required_from_host_keys != NULL) {
		switch (match_host_and_ip(remote_host, remote_ip,
		    opts->required_from_host_keys )) {
		case 1:
			/* Host name matches. */
			break;
		case -1:
		default:
			debug("%s: invalid from criteria", loc);
			auth_debug_add("%s: invalid from criteria", loc);
			/* FALLTHROUGH */
		case 0:
			logit("%s: Authentication tried for %.100s with "
			    "correct key but not from a permitted "
			    "host (host=%.200s, ip=%.200s, required=%.200s).",
			    loc, pw->pw_name, remote_host, remote_ip,
			    opts->required_from_host_keys);
			auth_debug_add("%s: Your host '%.200s' is not "
			    "permitted to use this key for login.",
			    loc, remote_host);
			/* deny access */
			return -1;
		}
	}
	/* Check source-address restriction from certificate */
	if (opts->required_from_host_cert != NULL) {
		switch (addr_match_cidr_list(remote_ip,
		    opts->required_from_host_cert)) {
		case 1:
			/* accepted */
			break;
		case -1:
		default:
			/* invalid */
			error("%s: Certificate source-address invalid",
			    loc);
			/* FALLTHROUGH */
		case 0:
			logit("%s: Authentication tried for %.100s with valid "
			    "certificate but not from a permitted source "
			    "address (%.200s).", loc, pw->pw_name, remote_ip);
			auth_debug_add("%s: Your address '%.200s' is not "
			    "permitted to use this certificate for login.",
			    loc, remote_ip);
			return -1;
		}
	}
	/*
	 *
	 * XXX this is spammy. We should report remotely only for keys
	 *     that are successful in actual auth attempts, and not PK_OK
	 *     tests.
	 */
	auth_log_authopts(loc, opts, 1);

	return 0;
}