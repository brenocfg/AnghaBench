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
struct json_token {struct json_token* string; struct json_token* name; struct json_token* sibling; struct json_token* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct json_token*) ; 

void json_free(struct json_token *json)
{
	if (!json)
		return;
	json_free(json->child);
	json_free(json->sibling);
	os_free(json->name);
	os_free(json->string);
	os_free(json);
}