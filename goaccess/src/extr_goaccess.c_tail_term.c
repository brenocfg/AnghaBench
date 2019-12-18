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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  not_empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  allocate_holder () ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_holder (int /*<<< orphan*/ *) ; 
 TYPE_1__ gdns_thread ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  main_win ; 
 int /*<<< orphan*/  main_win_height ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_screens () ; 
 int /*<<< orphan*/  term_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tail_term (void)
{
  pthread_mutex_lock (&gdns_thread.mutex);
  free_holder (&holder);
  pthread_cond_broadcast (&gdns_thread.not_empty);
  pthread_mutex_unlock (&gdns_thread.mutex);

  free_dashboard (dash);
  allocate_holder ();
  allocate_data ();

  term_size (main_win, &main_win_height);
  render_screens ();
}