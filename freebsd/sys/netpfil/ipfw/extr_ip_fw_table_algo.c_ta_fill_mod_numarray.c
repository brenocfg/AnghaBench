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
typedef  scalar_t__ uint64_t ;
struct table_info {int dummy; } ;
struct numarray_cfg {scalar_t__ size; int used; int /*<<< orphan*/  main_ptr; } ;
struct numarray {int dummy; } ;
struct mod_item {scalar_t__ size; int /*<<< orphan*/  main_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ta_fill_mod_numarray(void *ta_state, struct table_info *ti, void *ta_buf,
    uint64_t *pflags)
{
	struct mod_item *mi;
	struct numarray_cfg *cfg;

	mi = (struct mod_item *)ta_buf;
	cfg = (struct numarray_cfg *)ta_state;

	/* Check if we still need to grow array */
	if (cfg->size >= mi->size) {
		*pflags = 0;
		return (0);
	}

	memcpy(mi->main_ptr, cfg->main_ptr, cfg->used * sizeof(struct numarray));

	return (0);
}