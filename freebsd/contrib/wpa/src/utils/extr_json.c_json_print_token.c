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
struct json_token {char* name; struct json_token* sibling; struct json_token* child; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  json_type_str (int /*<<< orphan*/ ) ; 
 int os_snprintf (char*,size_t,char*,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 size_t os_strlen (char*) ; 

__attribute__((used)) static void json_print_token(struct json_token *token, int depth,
			     char *buf, size_t buflen)
{
	size_t len;
	int ret;

	if (!token)
		return;
	len = os_strlen(buf);
	ret = os_snprintf(buf + len, buflen - len, "[%d:%s:%s]",
			  depth, json_type_str(token->type),
			  token->name ? token->name : "");
	if (os_snprintf_error(buflen - len, ret)) {
		buf[len] = '\0';
		return;
	}
	json_print_token(token->child, depth + 1, buf, buflen);
	json_print_token(token->sibling, depth, buf, buflen);
}