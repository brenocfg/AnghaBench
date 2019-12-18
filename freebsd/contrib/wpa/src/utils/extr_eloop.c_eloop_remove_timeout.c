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
struct eloop_timeout {int /*<<< orphan*/  user_data; int /*<<< orphan*/  eloop_data; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop ; 
 int /*<<< orphan*/  os_free (struct eloop_timeout*) ; 
 int /*<<< orphan*/  user ; 
 int /*<<< orphan*/  wpa_trace_remove_ref (struct eloop_timeout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eloop_remove_timeout(struct eloop_timeout *timeout)
{
	dl_list_del(&timeout->list);
	wpa_trace_remove_ref(timeout, eloop, timeout->eloop_data);
	wpa_trace_remove_ref(timeout, user, timeout->user_data);
	os_free(timeout);
}