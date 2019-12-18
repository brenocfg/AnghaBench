#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct grep_source {int dummy; } ;
struct grep_opt {scalar_t__ binary; TYPE_1__* repo; } ;
struct TYPE_5__ {int /*<<< orphan*/  out; scalar_t__ done; struct grep_source source; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 scalar_t__ GREP_BINARY_TEXT ; 
 int /*<<< orphan*/  cond_add ; 
 int /*<<< orphan*/  cond_write ; 
 int /*<<< orphan*/  grep_lock () ; 
 int /*<<< orphan*/  grep_mutex ; 
 int /*<<< orphan*/  grep_source_load_driver (struct grep_source*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grep_unlock () ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 
 TYPE_2__* todo ; 
 int todo_done ; 
 int todo_end ; 

__attribute__((used)) static void add_work(struct grep_opt *opt, const struct grep_source *gs)
{
	grep_lock();

	while ((todo_end+1) % ARRAY_SIZE(todo) == todo_done) {
		pthread_cond_wait(&cond_write, &grep_mutex);
	}

	todo[todo_end].source = *gs;
	if (opt->binary != GREP_BINARY_TEXT)
		grep_source_load_driver(&todo[todo_end].source,
					opt->repo->index);
	todo[todo_end].done = 0;
	strbuf_reset(&todo[todo_end].out);
	todo_end = (todo_end + 1) % ARRAY_SIZE(todo);

	pthread_cond_signal(&cond_add);
	grep_unlock();
}