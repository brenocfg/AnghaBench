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
struct json_token {scalar_t__ type; scalar_t__ name; struct json_token* sibling; struct json_token* child; } ;

/* Variables and functions */
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ os_strcmp (scalar_t__,char const*) ; 

struct json_token * json_get_member(struct json_token *json, const char *name)
{
	struct json_token *token, *ret = NULL;

	if (!json || json->type != JSON_OBJECT)
		return NULL;
	/* Return last matching entry */
	for (token = json->child; token; token = token->sibling) {
		if (token->name && os_strcmp(token->name, name) == 0)
			ret = token;
	}
	return ret;
}