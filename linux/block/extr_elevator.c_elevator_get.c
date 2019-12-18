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
struct request_queue {int /*<<< orphan*/  required_elevator_features; } ;
struct elevator_type {int /*<<< orphan*/  elevator_owner; } ;

/* Variables and functions */
 struct elevator_type* elevator_find (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elv_list_lock ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct elevator_type *elevator_get(struct request_queue *q,
					  const char *name, bool try_loading)
{
	struct elevator_type *e;

	spin_lock(&elv_list_lock);

	e = elevator_find(name, q->required_elevator_features);
	if (!e && try_loading) {
		spin_unlock(&elv_list_lock);
		request_module("%s-iosched", name);
		spin_lock(&elv_list_lock);
		e = elevator_find(name, q->required_elevator_features);
	}

	if (e && !try_module_get(e->elevator_owner))
		e = NULL;

	spin_unlock(&elv_list_lock);
	return e;
}