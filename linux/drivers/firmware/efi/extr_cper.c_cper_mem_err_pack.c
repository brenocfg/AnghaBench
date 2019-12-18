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
struct cper_sec_mem_err {int /*<<< orphan*/  mem_dev_handle; int /*<<< orphan*/  mem_array_handle; int /*<<< orphan*/  rank; int /*<<< orphan*/  target_id; int /*<<< orphan*/  responder_id; int /*<<< orphan*/  requestor_id; int /*<<< orphan*/  bit_pos; int /*<<< orphan*/  column; int /*<<< orphan*/  row; int /*<<< orphan*/  device; int /*<<< orphan*/  bank; int /*<<< orphan*/  module; int /*<<< orphan*/  card; int /*<<< orphan*/  node; int /*<<< orphan*/  validation_bits; } ;
struct cper_mem_err_compact {int /*<<< orphan*/  mem_dev_handle; int /*<<< orphan*/  mem_array_handle; int /*<<< orphan*/  rank; int /*<<< orphan*/  target_id; int /*<<< orphan*/  responder_id; int /*<<< orphan*/  requestor_id; int /*<<< orphan*/  bit_pos; int /*<<< orphan*/  column; int /*<<< orphan*/  row; int /*<<< orphan*/  device; int /*<<< orphan*/  bank; int /*<<< orphan*/  module; int /*<<< orphan*/  card; int /*<<< orphan*/  node; int /*<<< orphan*/  validation_bits; } ;

/* Variables and functions */

void cper_mem_err_pack(const struct cper_sec_mem_err *mem,
		       struct cper_mem_err_compact *cmem)
{
	cmem->validation_bits = mem->validation_bits;
	cmem->node = mem->node;
	cmem->card = mem->card;
	cmem->module = mem->module;
	cmem->bank = mem->bank;
	cmem->device = mem->device;
	cmem->row = mem->row;
	cmem->column = mem->column;
	cmem->bit_pos = mem->bit_pos;
	cmem->requestor_id = mem->requestor_id;
	cmem->responder_id = mem->responder_id;
	cmem->target_id = mem->target_id;
	cmem->rank = mem->rank;
	cmem->mem_array_handle = mem->mem_array_handle;
	cmem->mem_dev_handle = mem->mem_dev_handle;
}