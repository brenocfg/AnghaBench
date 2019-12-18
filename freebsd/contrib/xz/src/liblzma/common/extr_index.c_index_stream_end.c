#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_4__ {int /*<<< orphan*/  groups; } ;
typedef  TYPE_1__ index_stream ;

/* Variables and functions */
 int /*<<< orphan*/  index_tree_end (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/  const*)) ; 
 int /*<<< orphan*/  lzma_free (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
index_stream_end(void *node, const lzma_allocator *allocator)
{
	index_stream *s = node;
	index_tree_end(&s->groups, allocator, &lzma_free);
	lzma_free(s, allocator);
	return;
}