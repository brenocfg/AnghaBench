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
struct intr_vector {int /*<<< orphan*/  iv_event; } ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 scalar_t__ intr_event_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr_stray_vector (struct intr_vector*) ; 

__attribute__((used)) static void
intr_execute_handlers(void *cookie)
{
	struct intr_vector *iv;

	iv = cookie;
	if (__predict_false(intr_event_handle(iv->iv_event, NULL) != 0))
		intr_stray_vector(iv);
}