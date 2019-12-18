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
struct object_entry {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cleanup_thread () ; 
 int /*<<< orphan*/  compare_ofs_delta_entry ; 
 int /*<<< orphan*/  compare_ref_delta_entry ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  init_thread () ; 
 scalar_t__ is_delta_type (int /*<<< orphan*/ ) ; 
 scalar_t__ nr_dispatched ; 
 int nr_objects ; 
 scalar_t__ nr_ofs_deltas ; 
 scalar_t__ nr_ref_deltas ; 
 int /*<<< orphan*/  nr_resolved_deltas ; 
 int nr_threads ; 
 struct object_entry* objects ; 
 int /*<<< orphan*/  ofs_deltas ; 
 int /*<<< orphan*/  progress ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_deltas ; 
 int /*<<< orphan*/  resolve_base (struct object_entry*) ; 
 scalar_t__ show_resolving_progress ; 
 int /*<<< orphan*/  start_progress (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strerror (int) ; 
 TYPE_1__* thread_data ; 
 int /*<<< orphan*/  threaded_second_pass ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void resolve_deltas(void)
{
	int i;

	if (!nr_ofs_deltas && !nr_ref_deltas)
		return;

	/* Sort deltas by base SHA1/offset for fast searching */
	QSORT(ofs_deltas, nr_ofs_deltas, compare_ofs_delta_entry);
	QSORT(ref_deltas, nr_ref_deltas, compare_ref_delta_entry);

	if (verbose || show_resolving_progress)
		progress = start_progress(_("Resolving deltas"),
					  nr_ref_deltas + nr_ofs_deltas);

	nr_dispatched = 0;
	if (nr_threads > 1 || getenv("GIT_FORCE_THREADS")) {
		init_thread();
		for (i = 0; i < nr_threads; i++) {
			int ret = pthread_create(&thread_data[i].thread, NULL,
						 threaded_second_pass, thread_data + i);
			if (ret)
				die(_("unable to create thread: %s"),
				    strerror(ret));
		}
		for (i = 0; i < nr_threads; i++)
			pthread_join(thread_data[i].thread, NULL);
		cleanup_thread();
		return;
	}

	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];

		if (is_delta_type(obj->type))
			continue;
		resolve_base(obj);
		display_progress(progress, nr_resolved_deltas);
	}
}