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
struct lio_stailq_node {int dummy; } ;
struct lio_stailq_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ STAILQ_EMPTY (struct lio_stailq_head*) ; 
 struct lio_stailq_node* STAILQ_FIRST (struct lio_stailq_head*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct lio_stailq_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 

__attribute__((used)) static inline struct lio_stailq_node *
lio_delete_first_node(struct lio_stailq_head *root)
{
	struct lio_stailq_node *node;

	if (STAILQ_EMPTY(root))
		node = NULL;
	else
		node = STAILQ_FIRST(root);

	if (node != NULL)
		STAILQ_REMOVE_HEAD(root, entries);

	return (node);
}