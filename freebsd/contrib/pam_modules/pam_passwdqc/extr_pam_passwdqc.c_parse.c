#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* min; unsigned long max; unsigned long passphrase_words; unsigned long match_length; int similar_deny; unsigned long random_bits; } ;
struct TYPE_5__ {int flags; unsigned long retry; TYPE_1__ qc; } ;
typedef  TYPE_2__ params_t ;
typedef  int /*<<< orphan*/  pam_handle_t ;

/* Variables and functions */
 int F_ASK_OLDAUTHTOK_MASK ; 
 int F_ASK_OLDAUTHTOK_PRELIM ; 
 int F_ASK_OLDAUTHTOK_UPDATE ; 
 int F_CHECK_OLDAUTHTOK ; 
 int F_ENFORCE_EVERYONE ; 
 int F_ENFORCE_MASK ; 
 int F_ENFORCE_USERS ; 
 int F_NON_UNIX ; 
 int F_USE_AUTHTOK ; 
 int F_USE_FIRST_PASS ; 
 unsigned long INT_MAX ; 
 int /*<<< orphan*/  MESSAGE_INVALID_OPTION ; 
 int /*<<< orphan*/  MESSAGE_MISCONFIGURED ; 
 int PAM_ABORT ; 
 int /*<<< orphan*/  PAM_ERROR_MSG ; 
 int PAM_SUCCESS ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  say (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int parse(params_t *params, pam_handle_t *pamh,
    int argc, const char **argv)
{
	const char *p;
	char *e;
	int i;
	unsigned long v;

	while (argc) {
		if (!strncmp(*argv, "min=", 4)) {
			p = *argv + 4;
			for (i = 0; i < 5; i++) {
				if (!strncmp(p, "disabled", 8)) {
					v = INT_MAX;
					p += 8;
				} else {
					v = strtoul(p, &e, 10);
					p = e;
				}
				if (i < 4 && *p++ != ',') break;
				if (v > INT_MAX) break;
				if (i && (int)v > params->qc.min[i - 1]) break;
				params->qc.min[i] = v;
			}
			if (*p) break;
		} else
		if (!strncmp(*argv, "max=", 4)) {
			v = strtoul(*argv + 4, &e, 10);
			if (*e || v < 8 || v > INT_MAX) break;
			params->qc.max = v;
		} else
		if (!strncmp(*argv, "passphrase=", 11)) {
			v = strtoul(*argv + 11, &e, 10);
			if (*e || v > INT_MAX) break;
			params->qc.passphrase_words = v;
		} else
		if (!strncmp(*argv, "match=", 6)) {
			v = strtoul(*argv + 6, &e, 10);
			if (*e || v > INT_MAX) break;
			params->qc.match_length = v;
		} else
		if (!strncmp(*argv, "similar=", 8)) {
			if (!strcmp(*argv + 8, "permit"))
				params->qc.similar_deny = 0;
			else
			if (!strcmp(*argv + 8, "deny"))
				params->qc.similar_deny = 1;
			else
				break;
		} else
		if (!strncmp(*argv, "random=", 7)) {
			v = strtoul(*argv + 7, &e, 10);
			if (!strcmp(e, ",only")) {
				e += 5;
				params->qc.min[4] = INT_MAX;
			}
			if (*e || v > INT_MAX) break;
			params->qc.random_bits = v;
		} else
		if (!strncmp(*argv, "enforce=", 8)) {
			params->flags &= ~F_ENFORCE_MASK;
			if (!strcmp(*argv + 8, "users"))
				params->flags |= F_ENFORCE_USERS;
			else
			if (!strcmp(*argv + 8, "everyone"))
				params->flags |= F_ENFORCE_EVERYONE;
			else
			if (strcmp(*argv + 8, "none"))
				break;
		} else
		if (!strcmp(*argv, "non-unix")) {
			if (params->flags & F_CHECK_OLDAUTHTOK) break;
			params->flags |= F_NON_UNIX;
		} else
		if (!strncmp(*argv, "retry=", 6)) {
			v = strtoul(*argv + 6, &e, 10);
			if (*e || v > INT_MAX) break;
			params->retry = v;
		} else
		if (!strncmp(*argv, "ask_oldauthtok", 14)) {
			params->flags &= ~F_ASK_OLDAUTHTOK_MASK;
			if (params->flags & F_USE_FIRST_PASS) break;
			if (!strcmp(*argv + 14, "=update"))
				params->flags |= F_ASK_OLDAUTHTOK_UPDATE;
			else
			if (!(*argv)[14])
				params->flags |= F_ASK_OLDAUTHTOK_PRELIM;
			else
				break;
		} else
		if (!strcmp(*argv, "check_oldauthtok")) {
			if (params->flags & F_NON_UNIX) break;
			params->flags |= F_CHECK_OLDAUTHTOK;
		} else
		if (!strcmp(*argv, "use_first_pass")) {
			if (params->flags & F_ASK_OLDAUTHTOK_MASK) break;
			params->flags |= F_USE_FIRST_PASS | F_USE_AUTHTOK;
		} else
		if (!strcmp(*argv, "use_authtok")) {
			params->flags |= F_USE_AUTHTOK;
		} else
			break;
		argc--; argv++;
	}

	if (argc) {
		if (getuid() != 0) {
			say(pamh, PAM_ERROR_MSG, MESSAGE_MISCONFIGURED);
		} else {
			say(pamh, PAM_ERROR_MSG, MESSAGE_INVALID_OPTION, *argv);
		}
		return PAM_ABORT;
	}

	return PAM_SUCCESS;
}