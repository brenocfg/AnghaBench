#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  not_empty; } ;
struct TYPE_3__ {size_t current; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  allocate_holder () ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_holder (int /*<<< orphan*/ *) ; 
 TYPE_2__ gdns_thread ; 
 TYPE_1__ gscroll ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  load_sort_win (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_win ; 
 int /*<<< orphan*/ * module_sort ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_screens () ; 

__attribute__((used)) static void
render_sort_dialog (void)
{
  load_sort_win (main_win, gscroll.current, &module_sort[gscroll.current]);

  pthread_mutex_lock (&gdns_thread.mutex);
  free_holder (&holder);
  pthread_cond_broadcast (&gdns_thread.not_empty);
  pthread_mutex_unlock (&gdns_thread.mutex);

  free_dashboard (dash);
  allocate_holder ();
  allocate_data ();
  render_screens ();
}