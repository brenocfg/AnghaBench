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
struct json_token {int dummy; } ;

/* Variables and functions */
 unsigned int JSON_MAX_TOKENS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct json_token* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct json_token * json_alloc_token(unsigned int *tokens)
{
	(*tokens)++;
	if (*tokens > JSON_MAX_TOKENS) {
		wpa_printf(MSG_DEBUG, "JSON: Maximum token limit exceeded");
		return NULL;
	}
	return os_zalloc(sizeof(struct json_token));
}