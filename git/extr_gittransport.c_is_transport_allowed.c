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
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  PROTOCOL_ALLOW_ALWAYS 130 
#define  PROTOCOL_ALLOW_NEVER 129 
#define  PROTOCOL_ALLOW_USER_ONLY 128 
 int get_protocol_config (char const*) ; 
 int git_env_bool (char*,int) ; 
 struct string_list* protocol_whitelist () ; 
 int string_list_has_string (struct string_list const*,char const*) ; 

int is_transport_allowed(const char *type, int from_user)
{
	const struct string_list *whitelist = protocol_whitelist();
	if (whitelist)
		return string_list_has_string(whitelist, type);

	switch (get_protocol_config(type)) {
	case PROTOCOL_ALLOW_ALWAYS:
		return 1;
	case PROTOCOL_ALLOW_NEVER:
		return 0;
	case PROTOCOL_ALLOW_USER_ONLY:
		if (from_user < 0)
			from_user = git_env_bool("GIT_PROTOCOL_FROM_USER", 1);
		return from_user;
	}

	BUG("invalid protocol_allow_config type");
}