#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {char const* const buf; } ;
struct TYPE_6__ {void* util; } ;
struct TYPE_5__ {void* util; } ;
struct TYPE_4__ {char* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (char**,int) ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const* const,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char const* const,char) ; 
 TYPE_3__* string_list_append (struct string_list*,char const* const) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 TYPE_2__* string_list_insert (struct string_list*,char const* const) ; 
 int /*<<< orphan*/  string_list_remove (struct string_list*,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 

__attribute__((used)) static char **prep_childenv(const char *const *deltaenv)
{
	extern char **environ;
	char **childenv;
	struct string_list env = STRING_LIST_INIT_DUP;
	struct strbuf key = STRBUF_INIT;
	const char *const *p;
	int i;

	/* Construct a sorted string list consisting of the current environ */
	for (p = (const char *const *) environ; p && *p; p++) {
		const char *equals = strchr(*p, '=');

		if (equals) {
			strbuf_reset(&key);
			strbuf_add(&key, *p, equals - *p);
			string_list_append(&env, key.buf)->util = (void *) *p;
		} else {
			string_list_append(&env, *p)->util = (void *) *p;
		}
	}
	string_list_sort(&env);

	/* Merge in 'deltaenv' with the current environ */
	for (p = deltaenv; p && *p; p++) {
		const char *equals = strchr(*p, '=');

		if (equals) {
			/* ('key=value'), insert or replace entry */
			strbuf_reset(&key);
			strbuf_add(&key, *p, equals - *p);
			string_list_insert(&env, key.buf)->util = (void *) *p;
		} else {
			/* otherwise ('key') remove existing entry */
			string_list_remove(&env, *p, 0);
		}
	}

	/* Create an array of 'char *' to be used as the childenv */
	ALLOC_ARRAY(childenv, env.nr + 1);
	for (i = 0; i < env.nr; i++)
		childenv[i] = env.items[i].util;
	childenv[env.nr] = NULL;

	string_list_clear(&env, 0);
	strbuf_release(&key);
	return childenv;
}