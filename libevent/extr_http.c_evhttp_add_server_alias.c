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
struct evhttp_server_alias {int /*<<< orphan*/  alias; } ;
struct evhttp {int /*<<< orphan*/  aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evhttp_server_alias*,int /*<<< orphan*/ ) ; 
 struct evhttp_server_alias* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct evhttp_server_alias*) ; 
 int /*<<< orphan*/  mm_strdup (char const*) ; 
 int /*<<< orphan*/  next ; 

int
evhttp_add_server_alias(struct evhttp *http, const char *alias)
{
	struct evhttp_server_alias *evalias;

	evalias = mm_calloc(1, sizeof(*evalias));
	if (!evalias)
		return -1;

	evalias->alias = mm_strdup(alias);
	if (!evalias->alias) {
		mm_free(evalias);
		return -1;
	}

	TAILQ_INSERT_TAIL(&http->aliases, evalias, next);

	return 0;
}