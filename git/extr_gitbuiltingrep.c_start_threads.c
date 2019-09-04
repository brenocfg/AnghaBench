#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grep_opt {scalar_t__ debug; int /*<<< orphan*/  output; } ;
struct TYPE_3__ {int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  compile_grep_patterns (struct grep_opt*) ; 
 int /*<<< orphan*/  cond_add ; 
 int /*<<< orphan*/  cond_result ; 
 int /*<<< orphan*/  cond_write ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grep_attr_mutex ; 
 int /*<<< orphan*/  grep_mutex ; 
 struct grep_opt* grep_opt_dup (struct grep_opt*) ; 
 int /*<<< orphan*/  grep_read_mutex ; 
 int grep_use_locks ; 
 int num_threads ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct grep_opt*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_out ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/ * threads ; 
 TYPE_1__* todo ; 
 int /*<<< orphan*/ * xcalloc (int,int) ; 

__attribute__((used)) static void start_threads(struct grep_opt *opt)
{
	int i;

	pthread_mutex_init(&grep_mutex, NULL);
	pthread_mutex_init(&grep_read_mutex, NULL);
	pthread_mutex_init(&grep_attr_mutex, NULL);
	pthread_cond_init(&cond_add, NULL);
	pthread_cond_init(&cond_write, NULL);
	pthread_cond_init(&cond_result, NULL);
	grep_use_locks = 1;

	for (i = 0; i < ARRAY_SIZE(todo); i++) {
		strbuf_init(&todo[i].out, 0);
	}

	threads = xcalloc(num_threads, sizeof(*threads));
	for (i = 0; i < num_threads; i++) {
		int err;
		struct grep_opt *o = grep_opt_dup(opt);
		o->output = strbuf_out;
		if (i)
			o->debug = 0;
		compile_grep_patterns(o);
		err = pthread_create(&threads[i], NULL, run, o);

		if (err)
			die(_("grep: failed to create thread: %s"),
			    strerror(err));
	}
}