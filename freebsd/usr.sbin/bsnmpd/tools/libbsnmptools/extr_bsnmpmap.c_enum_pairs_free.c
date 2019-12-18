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
struct enum_pairs {struct enum_pairs* enum_str; } ;
struct enum_pair {struct enum_pair* enum_str; } ;

/* Variables and functions */
 struct enum_pairs* STAILQ_FIRST (struct enum_pairs*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct enum_pairs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct enum_pairs*) ; 
 int /*<<< orphan*/  link ; 

void
enum_pairs_free(struct enum_pairs *headp)
{
	struct enum_pair *e;

	if (headp == NULL)
		return;

	while ((e = STAILQ_FIRST(headp)) != NULL) {
		STAILQ_REMOVE_HEAD(headp, link);

		if (e->enum_str)
			free(e->enum_str);
		free(e);
	}

	free(headp);
}