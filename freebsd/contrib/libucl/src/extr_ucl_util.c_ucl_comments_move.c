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

/* Variables and functions */
 int /*<<< orphan*/  ucl_object_delete_keyl (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ucl_object_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/ * ucl_object_lookup_len (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * ucl_object_ref (int /*<<< orphan*/  const*) ; 

bool
ucl_comments_move (ucl_object_t *comments,
		const ucl_object_t *from, const ucl_object_t *to)
{
	const ucl_object_t *found;
	ucl_object_t *obj;

	if (comments && from && to) {
		found = ucl_object_lookup_len (comments,
				(const char *)&from, sizeof (void *));

		if (found) {
			/* Replace key */
			obj = ucl_object_ref (found);
			ucl_object_delete_keyl (comments, (const char *)&from,
					sizeof (void *));
			ucl_object_insert_key (comments, obj, (const char *)&to,
					sizeof (void *), true);

			return true;
		}
	}

	return false;
}