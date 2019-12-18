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
struct json_token {scalar_t__ type; char const* string; struct json_token* sibling; struct json_token* child; } ;

/* Variables and functions */
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_STRING ; 
 scalar_t__ dpp_compatible_netrole (char const*,char const*) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 scalar_t__ os_strcmp (char const*,char const*) ; 

__attribute__((used)) static int dpp_connector_compatible_group(struct json_token *root,
					  const char *group_id,
					  const char *net_role)
{
	struct json_token *groups, *token;

	groups = json_get_member(root, "groups");
	if (!groups || groups->type != JSON_ARRAY)
		return 0;

	for (token = groups->child; token; token = token->sibling) {
		struct json_token *id, *role;

		id = json_get_member(token, "groupId");
		if (!id || id->type != JSON_STRING)
			continue;

		role = json_get_member(token, "netRole");
		if (!role || role->type != JSON_STRING)
			continue;

		if (os_strcmp(id->string, "*") != 0 &&
		    os_strcmp(group_id, "*") != 0 &&
		    os_strcmp(id->string, group_id) != 0)
			continue;

		if (dpp_compatible_netrole(role->string, net_role))
			return 1;
	}

	return 0;
}