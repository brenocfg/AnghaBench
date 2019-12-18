#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  table; } ;
struct decode_table {TYPE_2__ table; } ;
struct TYPE_3__ {int bits; } ;
struct decode_header {TYPE_1__ type_regs; } ;
struct coverage_table {int num_entries; int /*<<< orphan*/  nesting; struct coverage_entry* base; } ;
struct coverage_entry {int matched; int /*<<< orphan*/  nesting; int /*<<< orphan*/  regs; struct decode_header const* header; } ;
typedef  enum decode_type { ____Placeholder_decode_type } decode_type ;

/* Variables and functions */
 int DECODE_TYPE_MASK ; 
 int DECODE_TYPE_TABLE ; 
 int ENOMEM ; 
 int MAX_COVERAGE_ENTRIES ; 
 int /*<<< orphan*/  coverage_start_registers (struct decode_header const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int table_iter (int /*<<< orphan*/ ,int (*) (struct decode_header const*,void*),struct coverage_table*) ; 

__attribute__((used)) static int coverage_start_fn(const struct decode_header *h, void *args)
{
	struct coverage_table *coverage = (struct coverage_table *)args;
	enum decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;
	struct coverage_entry *entry = coverage->base + coverage->num_entries;

	if (coverage->num_entries == MAX_COVERAGE_ENTRIES - 1) {
		pr_err("FAIL: Out of space for test coverage data");
		return -ENOMEM;
	}

	++coverage->num_entries;

	entry->header = h;
	entry->regs = coverage_start_registers(h);
	entry->nesting = coverage->nesting;
	entry->matched = false;

	if (type == DECODE_TYPE_TABLE) {
		struct decode_table *d = (struct decode_table *)h;
		int ret;
		++coverage->nesting;
		ret = table_iter(d->table.table, coverage_start_fn, coverage);
		--coverage->nesting;
		return ret;
	}

	return 0;
}