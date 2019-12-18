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
struct thread_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_thread_lwp_callback ; 
 struct thread_info* iterate_over_threads (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static struct thread_info *
find_thread_lwp (int lwpid)
{
  return iterate_over_threads (find_thread_lwp_callback, (void *)lwpid);
}