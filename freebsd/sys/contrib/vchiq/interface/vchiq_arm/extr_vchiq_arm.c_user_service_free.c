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
struct TYPE_3__ {int /*<<< orphan*/  remove_event; int /*<<< orphan*/  insert_event; } ;
typedef  TYPE_1__ USER_SERVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  _sema_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void
user_service_free(void *userdata)
{
	USER_SERVICE_T *user_service = userdata;
	
	_sema_destroy(&user_service->insert_event);
	_sema_destroy(&user_service->remove_event);

	kfree(user_service);
}