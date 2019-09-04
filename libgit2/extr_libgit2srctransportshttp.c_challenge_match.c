#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ git_http_auth_scheme ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

__attribute__((used)) static bool challenge_match(git_http_auth_scheme *scheme, void *data)
{
	const char *scheme_name = scheme->name;
	const char *challenge = (const char *)data;
	size_t scheme_len;

	scheme_len = strlen(scheme_name);
	return (strncasecmp(challenge, scheme_name, scheme_len) == 0 &&
		(challenge[scheme_len] == '\0' || challenge[scheme_len] == ' '));
}