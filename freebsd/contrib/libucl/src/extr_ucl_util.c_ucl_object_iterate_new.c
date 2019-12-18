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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  int /*<<< orphan*/  ucl_object_iter_t ;
struct ucl_object_safe_iter {int /*<<< orphan*/  const* impl_it; int /*<<< orphan*/ * expl_it; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 struct ucl_object_safe_iter* UCL_ALLOC (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_iter_magic ; 

ucl_object_iter_t
ucl_object_iterate_new (const ucl_object_t *obj)
{
	struct ucl_object_safe_iter *it;

	it = UCL_ALLOC (sizeof (*it));
	if (it != NULL) {
		memcpy (it->magic, safe_iter_magic, sizeof (it->magic));
		it->expl_it = NULL;
		it->impl_it = obj;
	}

	return (ucl_object_iter_t)it;
}