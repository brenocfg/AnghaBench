#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  truncated ;
struct passwd {char const* pw_name; char const* pw_gecos; } ;
struct TYPE_6__ {int* min; int max; scalar_t__ similar_deny; } ;
typedef  TYPE_1__ passwdqc_params_t ;

/* Variables and functions */
 char* REASON_ERROR ; 
 char* REASON_LONG ; 
 char* REASON_PERSONAL ; 
 char* REASON_SAME ; 
 char* REASON_SHORT ; 
 char* REASON_SIMILAR ; 
 char* REASON_SIMPLE ; 
 char* REASON_SIMPLESHORT ; 
 char* REASON_WORD ; 
 int /*<<< orphan*/  clean (char*) ; 
 scalar_t__ is_based (TYPE_1__*,char*,char*,char const*) ; 
 scalar_t__ is_simple (TYPE_1__*,char const*) ; 
 scalar_t__ is_word_based (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* reverse (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 char* unify (char const*) ; 

const char *_passwdqc_check(passwdqc_params_t *params,
    const char *newpass, const char *oldpass, struct passwd *pw)
{
	char truncated[9], *reversed;
	char *u_newpass, *u_reversed;
	char *u_oldpass;
	char *u_name, *u_gecos;
	const char *reason;
	int length;

	reversed = NULL;
	u_newpass = u_reversed = NULL;
	u_oldpass = NULL;
	u_name = u_gecos = NULL;

	reason = NULL;

	if (oldpass && !strcmp(oldpass, newpass))
		reason = REASON_SAME;

	length = strlen(newpass);

	if (!reason && length < params->min[4])
		reason = REASON_SHORT;

	if (!reason && length > params->max) {
		if (params->max == 8) {
			truncated[0] = '\0';
			strncat(truncated, newpass, 8);
			newpass = truncated;
			if (oldpass && !strncmp(oldpass, newpass, 8))
				reason = REASON_SAME;
		} else
			reason = REASON_LONG;
	}

	if (!reason && is_simple(params, newpass)) {
		if (length < params->min[1] && params->min[1] <= params->max)
			reason = REASON_SIMPLESHORT;
		else
			reason = REASON_SIMPLE;
	}

	if (!reason) {
		if ((reversed = reverse(newpass))) {
			u_newpass = unify(newpass);
			u_reversed = unify(reversed);
			if (oldpass)
				u_oldpass = unify(oldpass);
			if (pw) {
				u_name = unify(pw->pw_name);
				u_gecos = unify(pw->pw_gecos);
			}
		}
		if (!reversed ||
		    !u_newpass || !u_reversed ||
		    (oldpass && !u_oldpass) ||
		    (pw && (!u_name || !u_gecos)))
			reason = REASON_ERROR;
	}

	if (!reason && oldpass && params->similar_deny &&
	    (is_based(params, u_oldpass, u_newpass, newpass) ||
	    is_based(params, u_oldpass, u_reversed, reversed)))
		reason = REASON_SIMILAR;

	if (!reason && pw &&
	    (is_based(params, u_name, u_newpass, newpass) ||
	    is_based(params, u_name, u_reversed, reversed) ||
	    is_based(params, u_gecos, u_newpass, newpass) ||
	    is_based(params, u_gecos, u_reversed, reversed)))
		reason = REASON_PERSONAL;

	if (!reason && (int)strlen(newpass) < params->min[2] &&
	    (is_word_based(params, u_newpass, newpass) ||
	    is_word_based(params, u_reversed, reversed)))
		reason = REASON_WORD;

	memset(truncated, 0, sizeof(truncated));
	clean(reversed);
	clean(u_newpass); clean(u_reversed);
	clean(u_oldpass);
	clean(u_name); clean(u_gecos);

	return reason;
}