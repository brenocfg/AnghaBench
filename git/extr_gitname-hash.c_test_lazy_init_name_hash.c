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
struct index_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lazy_init_name_hash (struct index_state*) ; 
 int lazy_nr_dir_threads ; 
 int lazy_try_threaded ; 

int test_lazy_init_name_hash(struct index_state *istate, int try_threaded)
{
	lazy_nr_dir_threads = 0;
	lazy_try_threaded = try_threaded;

	lazy_init_name_hash(istate);

	return lazy_nr_dir_threads;
}