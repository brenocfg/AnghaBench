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
struct trailer_item {int /*<<< orphan*/  token; } ;
struct arg_item {int /*<<< orphan*/  token; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t token_len_without_separator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int same_token(struct trailer_item *a, struct arg_item *b)
{
	size_t a_len, b_len, min_len;

	if (!a->token)
		return 0;

	a_len = token_len_without_separator(a->token, strlen(a->token));
	b_len = token_len_without_separator(b->token, strlen(b->token));
	min_len = (a_len > b_len) ? b_len : a_len;

	return !strncasecmp(a->token, b->token, min_len);
}