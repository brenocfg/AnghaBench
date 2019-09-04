#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ key; scalar_t__ name; } ;
struct arg_item {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncasecmp (char const*,scalar_t__,size_t) ; 

__attribute__((used)) static int token_matches_item(const char *tok, struct arg_item *item, size_t tok_len)
{
	if (!strncasecmp(tok, item->conf.name, tok_len))
		return 1;
	return item->conf.key ? !strncasecmp(tok, item->conf.key, tok_len) : 0;
}