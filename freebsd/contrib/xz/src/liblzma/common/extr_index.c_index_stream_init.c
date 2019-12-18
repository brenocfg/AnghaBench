#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* lzma_vli ;
typedef  int /*<<< orphan*/  lzma_allocator ;
struct TYPE_7__ {int /*<<< orphan*/  version; } ;
struct TYPE_6__ {int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/ * parent; void* compressed_base; void* uncompressed_base; } ;
struct TYPE_8__ {scalar_t__ stream_padding; TYPE_2__ stream_flags; scalar_t__ index_list_size; scalar_t__ record_count; int /*<<< orphan*/  groups; void* block_number_base; int /*<<< orphan*/  number; TYPE_1__ node; } ;
typedef  TYPE_3__ index_stream ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  index_tree_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* lzma_alloc (int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static index_stream *
index_stream_init(lzma_vli compressed_base, lzma_vli uncompressed_base,
		uint32_t stream_number, lzma_vli block_number_base,
		const lzma_allocator *allocator)
{
	index_stream *s = lzma_alloc(sizeof(index_stream), allocator);
	if (s == NULL)
		return NULL;

	s->node.uncompressed_base = uncompressed_base;
	s->node.compressed_base = compressed_base;
	s->node.parent = NULL;
	s->node.left = NULL;
	s->node.right = NULL;

	s->number = stream_number;
	s->block_number_base = block_number_base;

	index_tree_init(&s->groups);

	s->record_count = 0;
	s->index_list_size = 0;
	s->stream_flags.version = UINT32_MAX;
	s->stream_padding = 0;

	return s;
}