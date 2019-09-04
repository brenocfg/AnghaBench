#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct tmp_objdir {TYPE_1__ path; int /*<<< orphan*/  env; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERNATE_DB_ENVIRONMENT ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  DB_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_QUARANTINE_ENVIRONMENT ; 
 int /*<<< orphan*/  absolute_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int /*<<< orphan*/  mkdtemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_tmp_objdir ; 
 int /*<<< orphan*/  remove_tmp_objdir_on_signal ; 
 scalar_t__ setup_tmp_objdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct tmp_objdir* the_tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_destroy (struct tmp_objdir*) ; 
 int /*<<< orphan*/  tmp_objdir_free (struct tmp_objdir*) ; 
 struct tmp_objdir* xmalloc (int) ; 

struct tmp_objdir *tmp_objdir_create(void)
{
	static int installed_handlers;
	struct tmp_objdir *t;

	if (the_tmp_objdir)
		BUG("only one tmp_objdir can be used at a time");

	t = xmalloc(sizeof(*t));
	strbuf_init(&t->path, 0);
	argv_array_init(&t->env);

	strbuf_addf(&t->path, "%s/incoming-XXXXXX", get_object_directory());

	/*
	 * Grow the strbuf beyond any filename we expect to be placed in it.
	 * If tmp_objdir_destroy() is called by a signal handler, then
	 * we should be able to use the strbuf to remove files without
	 * having to call malloc.
	 */
	strbuf_grow(&t->path, 1024);

	if (!mkdtemp(t->path.buf)) {
		/* free, not destroy, as we never touched the filesystem */
		tmp_objdir_free(t);
		return NULL;
	}

	the_tmp_objdir = t;
	if (!installed_handlers) {
		atexit(remove_tmp_objdir);
		sigchain_push_common(remove_tmp_objdir_on_signal);
		installed_handlers++;
	}

	if (setup_tmp_objdir(t->path.buf)) {
		tmp_objdir_destroy(t);
		return NULL;
	}

	env_append(&t->env, ALTERNATE_DB_ENVIRONMENT,
		   absolute_path(get_object_directory()));
	env_replace(&t->env, DB_ENVIRONMENT, absolute_path(t->path.buf));
	env_replace(&t->env, GIT_QUARANTINE_ENVIRONMENT,
		    absolute_path(t->path.buf));

	return t;
}