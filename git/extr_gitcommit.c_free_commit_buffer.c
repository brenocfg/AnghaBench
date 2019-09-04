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
struct parsed_object_pool {int /*<<< orphan*/  buffer_slab; } ;
struct commit_buffer {scalar_t__ size; int /*<<< orphan*/  buffer; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 struct commit_buffer* buffer_slab_peek (int /*<<< orphan*/ ,struct commit*) ; 

void free_commit_buffer(struct parsed_object_pool *pool, struct commit *commit)
{
	struct commit_buffer *v = buffer_slab_peek(
		pool->buffer_slab, commit);
	if (v) {
		FREE_AND_NULL(v->buffer);
		v->size = 0;
	}
}