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
struct TYPE_3__ {int pack_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  counter_mutex ; 
 int /*<<< orphan*/  curr_pack ; 
 int /*<<< orphan*/  deepest_delta_mutex ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_recursive_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key ; 
 int nr_threads ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mutex ; 
 scalar_t__ show_stat ; 
 TYPE_1__* thread_data ; 
 int threads_active ; 
 int /*<<< orphan*/  type_cas_mutex ; 
 int /*<<< orphan*/  work_mutex ; 
 TYPE_1__* xcalloc (int,int) ; 

__attribute__((used)) static void init_thread(void)
{
	int i;
	init_recursive_mutex(&read_mutex);
	pthread_mutex_init(&counter_mutex, NULL);
	pthread_mutex_init(&work_mutex, NULL);
	pthread_mutex_init(&type_cas_mutex, NULL);
	if (show_stat)
		pthread_mutex_init(&deepest_delta_mutex, NULL);
	pthread_key_create(&key, NULL);
	thread_data = xcalloc(nr_threads, sizeof(*thread_data));
	for (i = 0; i < nr_threads; i++) {
		thread_data[i].pack_fd = open(curr_pack, O_RDONLY);
		if (thread_data[i].pack_fd == -1)
			die_errno(_("unable to open %s"), curr_pack);
	}

	threads_active = 1;
}