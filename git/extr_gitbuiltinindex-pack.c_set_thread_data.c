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
struct thread_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct thread_local*) ; 
 scalar_t__ threads_active ; 

__attribute__((used)) static void set_thread_data(struct thread_local *data)
{
	if (threads_active)
		pthread_setspecific(key, data);
}