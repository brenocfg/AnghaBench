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
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_get_method (struct event_base*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int base_supports_et(struct event_base *base)
{
	return
		(!strcmp(event_base_get_method(base), "epoll") ||
		!strcmp(event_base_get_method(base), "epoll (with changelist)") ||
		!strcmp(event_base_get_method(base), "kqueue"));
}