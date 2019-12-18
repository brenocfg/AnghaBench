#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* sparse_vector_t ;
struct TYPE_3__ {int max_idx; void** array; int /*<<< orphan*/  os; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPV_ROWLEN ; 
 void** spv_new_row (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
*spv_new_cell(sparse_vector_t sv, uint32_t idx, uint8_t alloc_new_rows)
{
	uint32_t a = (idx >> 16) & 0xff;
	uint32_t b = (idx >>  8) & 0xff;
	uint32_t c = (idx >>  0) & 0xff;
	void **p;

	if (idx >= sv->max_idx) {
		return NULL;
	}

	if (sv->array == NULL) {
		sv->array = (alloc_new_rows ? spv_new_row(sv->os, SPV_ROWLEN) : NULL);
		if (sv->array == NULL) {
			return NULL;
		}
	}
	p = sv->array;
	if (p[a] == NULL) {
		p[a] = (alloc_new_rows ? spv_new_row(sv->os, SPV_ROWLEN) : NULL);
		if (p[a] == NULL) {
			return NULL;
		}
	}
	p = p[a];
	if (p[b] == NULL) {
		p[b] = (alloc_new_rows ? spv_new_row(sv->os, SPV_ROWLEN) : NULL);
		if (p[b] == NULL) {
			return NULL;
		}
	}
	p = p[b];

	return &p[c];
}