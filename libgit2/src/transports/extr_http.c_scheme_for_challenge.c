#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int credtypes; } ;
typedef  TYPE_1__ git_http_auth_scheme ;
typedef  int git_credtype_t ;
struct TYPE_8__ {int const credtype; } ;
typedef  TYPE_2__ git_cred ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* auth_schemes ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static git_http_auth_scheme *scheme_for_challenge(
	const char *challenge,
	git_cred *cred)
{
	git_http_auth_scheme *scheme = NULL;
	size_t i;

	for (i = 0; i < ARRAY_SIZE(auth_schemes); i++) {
		const char *scheme_name = auth_schemes[i].name;
		const git_credtype_t scheme_types = auth_schemes[i].credtypes;
		size_t scheme_len;

		scheme_len = strlen(scheme_name);

		if ((!cred || (cred->credtype & scheme_types)) &&
		    strncasecmp(challenge, scheme_name, scheme_len) == 0 &&
		    (challenge[scheme_len] == '\0' || challenge[scheme_len] == ' ')) {
			scheme = &auth_schemes[i];
			break;
		}
	}

	return scheme;
}