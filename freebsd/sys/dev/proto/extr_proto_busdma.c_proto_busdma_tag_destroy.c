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
struct proto_tag {int /*<<< orphan*/ * parent; int /*<<< orphan*/  children; int /*<<< orphan*/  mds; } ;
struct proto_busdma {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct proto_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROTO_BUSDMA ; 
 int /*<<< orphan*/  free (struct proto_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peers ; 
 int /*<<< orphan*/  tags ; 

__attribute__((used)) static int
proto_busdma_tag_destroy(struct proto_busdma *busdma, struct proto_tag *tag)
{

	if (!LIST_EMPTY(&tag->mds))
		return (EBUSY);
	if (!LIST_EMPTY(&tag->children))
		return (EBUSY);

	if (tag->parent != NULL) {
		LIST_REMOVE(tag, peers);
		tag->parent = NULL;
	}
	LIST_REMOVE(tag, tags);
	free(tag, M_PROTO_BUSDMA);
	return (0);
}