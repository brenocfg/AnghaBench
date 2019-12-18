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
 int /*<<< orphan*/  ucl_object_fromstring (char const*) ; 
 int /*<<< orphan*/  ucl_object_insert_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int) ; 

void
ucl_comments_add (ucl_object_t *comments, const ucl_object_t *obj,
		const char *comment)
{
	if (comments && obj && comment) {
		ucl_object_insert_key (comments, ucl_object_fromstring (comment),
				(const char *)&obj, sizeof (void *), true);
	}
}