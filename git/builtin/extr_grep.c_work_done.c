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
struct TYPE_2__ {size_t len; char* buf; } ;
struct work_item {int done; int /*<<< orphan*/  source; TYPE_1__ out; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct work_item*) ; 
 scalar_t__ all_work_added ; 
 int /*<<< orphan*/  cond_result ; 
 int /*<<< orphan*/  cond_write ; 
 int /*<<< orphan*/  grep_lock () ; 
 int /*<<< orphan*/  grep_source_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  grep_unlock () ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 scalar_t__ skip_first_line ; 
 struct work_item* todo ; 
 size_t todo_done ; 
 size_t todo_end ; 
 size_t todo_start ; 
 int /*<<< orphan*/  write_or_die (int,char const*,size_t) ; 

__attribute__((used)) static void work_done(struct work_item *w)
{
	int old_done;

	grep_lock();
	w->done = 1;
	old_done = todo_done;
	for(; todo[todo_done].done && todo_done != todo_start;
	    todo_done = (todo_done+1) % ARRAY_SIZE(todo)) {
		w = &todo[todo_done];
		if (w->out.len) {
			const char *p = w->out.buf;
			size_t len = w->out.len;

			/* Skip the leading hunk mark of the first file. */
			if (skip_first_line) {
				while (len) {
					len--;
					if (*p++ == '\n')
						break;
				}
				skip_first_line = 0;
			}

			write_or_die(1, p, len);
		}
		grep_source_clear(&w->source);
	}

	if (old_done != todo_done)
		pthread_cond_signal(&cond_write);

	if (all_work_added && todo_done == todo_end)
		pthread_cond_signal(&cond_result);

	grep_unlock();
}