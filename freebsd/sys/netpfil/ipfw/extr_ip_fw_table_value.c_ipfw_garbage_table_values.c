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
typedef  int uint32_t ;
struct tentry_info {scalar_t__ value; int flags; } ;
struct table_value {int dummy; } ;
struct table_config {int dummy; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int TEI_FLAGS_ADDED ; 
 int /*<<< orphan*/  get_value_ptrs (struct ip_fw_chain*,struct table_config*,int,struct table_value**,struct namedobj_instance**) ; 
 int /*<<< orphan*/  unref_table_value (struct namedobj_instance*,struct table_value*,scalar_t__) ; 

void
ipfw_garbage_table_values(struct ip_fw_chain *ch, struct table_config *tc,
    struct tentry_info *tei, uint32_t count, int rollback)
{
	int i;
	struct tentry_info *ptei;
	struct table_value *pval;
	struct namedobj_instance *vi;

	/*
	 * We have two slightly different ADD cases here:
	 * either (1) we are successful / partially successful,
	 * in that case we need
	 * * to ignore ADDED entries values
	 * * rollback every other values (either UPDATED since
	 *   old value has been stored there, or some failure like
	 *   EXISTS or LIMIT or simply "ignored" case.
	 *
	 * (2): atomic rollback of partially successful operation
	 * in that case we simply need to unref all entries.
	 *
	 * DELETE case is simpler: no atomic support there, so
	 * we simply unref all non-zero values.
	 */

	/*
	 * Get current table value pointers.
	 * XXX: Properly read vshared
	 */
	get_value_ptrs(ch, tc, 1, &pval, &vi);

	for (i = 0; i < count; i++) {
		ptei = &tei[i];

		if (ptei->value == 0) {

			/*
			 * We may be deleting non-existing record.
			 * Skip.
			 */
			continue;
		}

		if ((ptei->flags & TEI_FLAGS_ADDED) != 0 && rollback == 0) {
			ptei->value = 0;
			continue;
		}

		unref_table_value(vi, pval, ptei->value);
		ptei->value = 0;
	}
}