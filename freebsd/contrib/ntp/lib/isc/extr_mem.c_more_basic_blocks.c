#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_4__ {int mem_target; unsigned int quota; size_t total; size_t basic_table_count; size_t basic_table_size; unsigned char** (* memalloc ) (int /*<<< orphan*/ ,unsigned int) ;unsigned char** basic_table; unsigned char* lowest; unsigned char* highest; void* basic_blocks; int /*<<< orphan*/  memalloc_failures; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* memfree ) (int /*<<< orphan*/ ,unsigned char**) ;} ;
typedef  TYPE_1__ isc__mem_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_2__ element ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int NUM_BASIC_BLOCKS ; 
 unsigned int TABLE_INCREMENT ; 
 int /*<<< orphan*/  memcpy (unsigned char**,unsigned char**,int) ; 
 unsigned char** stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned char**) ; 
 unsigned char** stub3 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline isc_boolean_t
more_basic_blocks(isc__mem_t *ctx) {
	void *new;
	unsigned char *curr, *next;
	unsigned char *first, *last;
	unsigned char **table;
	unsigned int table_size;
	size_t increment;
	int i;

	/* Require: we hold the context lock. */

	/*
	 * Did we hit the quota for this context?
	 */
	increment = NUM_BASIC_BLOCKS * ctx->mem_target;
	if (ctx->quota != 0U && ctx->total + increment > ctx->quota)
		return (ISC_FALSE);

	INSIST(ctx->basic_table_count <= ctx->basic_table_size);
	if (ctx->basic_table_count == ctx->basic_table_size) {
		table_size = ctx->basic_table_size + TABLE_INCREMENT;
		table = (ctx->memalloc)(ctx->arg,
					table_size * sizeof(unsigned char *));
		if (table == NULL) {
			ctx->memalloc_failures++;
			return (ISC_FALSE);
		}
		if (ctx->basic_table_size != 0) {
			memcpy(table, ctx->basic_table,
			       ctx->basic_table_size *
			       sizeof(unsigned char *));
			(ctx->memfree)(ctx->arg, ctx->basic_table);
		}
		ctx->basic_table = table;
		ctx->basic_table_size = table_size;
	}

	new = (ctx->memalloc)(ctx->arg, NUM_BASIC_BLOCKS * ctx->mem_target);
	if (new == NULL) {
		ctx->memalloc_failures++;
		return (ISC_FALSE);
	}
	ctx->total += increment;
	ctx->basic_table[ctx->basic_table_count] = new;
	ctx->basic_table_count++;

	curr = new;
	next = curr + ctx->mem_target;
	for (i = 0; i < (NUM_BASIC_BLOCKS - 1); i++) {
		((element *)curr)->next = (element *)next;
		curr = next;
		next += ctx->mem_target;
	}
	/*
	 * curr is now pointing at the last block in the
	 * array.
	 */
	((element *)curr)->next = NULL;
	first = new;
	last = first + NUM_BASIC_BLOCKS * ctx->mem_target - 1;
	if (first < ctx->lowest || ctx->lowest == NULL)
		ctx->lowest = first;
	if (last > ctx->highest)
		ctx->highest = last;
	ctx->basic_blocks = new;

	return (ISC_TRUE);
}