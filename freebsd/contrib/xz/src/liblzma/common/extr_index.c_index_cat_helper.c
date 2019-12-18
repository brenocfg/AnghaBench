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
struct TYPE_8__ {int /*<<< orphan*/  compressed_base; int /*<<< orphan*/  uncompressed_base; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_6__ {TYPE_3__ node; int /*<<< orphan*/  block_number_base; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ index_stream ;
struct TYPE_7__ {int /*<<< orphan*/  streams; scalar_t__ block_number_add; scalar_t__ stream_number_add; scalar_t__ file_size; scalar_t__ uncompressed_size; } ;
typedef  TYPE_2__ index_cat_info ;

/* Variables and functions */
 int /*<<< orphan*/  index_tree_append (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
index_cat_helper(const index_cat_info *info, index_stream *this)
{
	index_stream *left = (index_stream *)(this->node.left);
	index_stream *right = (index_stream *)(this->node.right);

	if (left != NULL)
		index_cat_helper(info, left);

	this->node.uncompressed_base += info->uncompressed_size;
	this->node.compressed_base += info->file_size;
	this->number += info->stream_number_add;
	this->block_number_base += info->block_number_add;
	index_tree_append(info->streams, &this->node);

	if (right != NULL)
		index_cat_helper(info, right);

	return;
}