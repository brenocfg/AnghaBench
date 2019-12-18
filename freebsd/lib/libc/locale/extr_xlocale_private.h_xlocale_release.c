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
struct xlocale_refcounted {int /*<<< orphan*/  (* destructor ) (struct xlocale_refcounted*) ;int /*<<< orphan*/  retain_count; } ;

/* Variables and functions */
 int atomic_fetchadd_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct xlocale_refcounted*) ; 

__attribute__((used)) __attribute__((unused)) static void
xlocale_release(void *val)
{
	struct xlocale_refcounted *obj = val;
	long count;

	count = atomic_fetchadd_long(&(obj->retain_count), -1) - 1;
	if (count < 0 && obj->destructor != NULL)
		obj->destructor(obj);
}