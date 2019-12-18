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
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

void clear_ref_exclusion(struct string_list **ref_excludes_p)
{
	if (*ref_excludes_p) {
		string_list_clear(*ref_excludes_p, 0);
		free(*ref_excludes_p);
	}
	*ref_excludes_p = NULL;
}