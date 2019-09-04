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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_data () ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  free_dashboard (int /*<<< orphan*/ ) ; 
 TYPE_1__ gdns_thread ; 
 int /*<<< orphan*/  gscroll ; 
 int /*<<< orphan*/  holder ; 
 int perform_next_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_screens () ; 

__attribute__((used)) static void
search_next_match (int search)
{
  pthread_mutex_lock (&gdns_thread.mutex);
  search = perform_next_find (holder, &gscroll);
  pthread_mutex_unlock (&gdns_thread.mutex);
  if (search != 0)
    return;

  free_dashboard (dash);
  allocate_data ();
  render_screens ();
}