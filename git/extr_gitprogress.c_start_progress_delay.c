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
typedef  int /*<<< orphan*/  uint64_t ;
struct progress {char const* title; int last_value; int last_percent; unsigned int delay; unsigned int sparse; scalar_t__ split; int /*<<< orphan*/  title_len; int /*<<< orphan*/  counters_sb; int /*<<< orphan*/  start_ns; int /*<<< orphan*/ * throughput; int /*<<< orphan*/  total; } ;

/* Variables and functions */
 int /*<<< orphan*/  getnanotime () ; 
 int /*<<< orphan*/  set_progress_signal () ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_strwidth (char const*) ; 
 struct progress* xmalloc (int) ; 

__attribute__((used)) static struct progress *start_progress_delay(const char *title, uint64_t total,
					     unsigned delay, unsigned sparse)
{
	struct progress *progress = xmalloc(sizeof(*progress));
	progress->title = title;
	progress->total = total;
	progress->last_value = -1;
	progress->last_percent = -1;
	progress->delay = delay;
	progress->sparse = sparse;
	progress->throughput = NULL;
	progress->start_ns = getnanotime();
	strbuf_init(&progress->counters_sb, 0);
	progress->title_len = utf8_strwidth(title);
	progress->split = 0;
	set_progress_signal();
	return progress;
}