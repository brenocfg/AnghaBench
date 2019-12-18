#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gcov_info {int n_functions; TYPE_1__** functions; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * next; } ;
struct gcov_fn_info {int dummy; } ;
struct gcov_ctr_info {int num; struct gcov_info* values; } ;
typedef  int /*<<< orphan*/  gcov_type ;
struct TYPE_2__ {struct gcov_ctr_info* ctrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GCOV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  gcov_info_free (struct gcov_info*) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct gcov_info*,struct gcov_info*,size_t) ; 
 unsigned int num_counter_active (struct gcov_info*) ; 
 int /*<<< orphan*/ * strdup_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct gcov_info *
gcov_info_dup(struct gcov_info *info)
{
	struct gcov_info *dup;
	struct gcov_ctr_info *dci_ptr; /* dst counter info */
	struct gcov_ctr_info *sci_ptr; /* src counter info */
	unsigned int active;
	unsigned int fi_idx; /* function info idx */
	unsigned int ct_idx; /* counter type idx */
	size_t fi_size; /* function info size */
	size_t cv_size; /* counter values size */

	if ((dup = malloc(sizeof(*dup), M_GCOV, M_NOWAIT|M_ZERO)) == NULL)
		return (NULL);
	memcpy(dup, info, sizeof(*dup));

	dup->next = NULL;
	dup->filename = NULL;
	dup->functions = NULL;

	dup->filename = strdup_flags(info->filename, M_GCOV, M_NOWAIT);
	if (dup->filename == NULL)
		goto err_free;

	dup->functions = malloc(info->n_functions * sizeof(struct gcov_fn_info *), M_GCOV, M_NOWAIT|M_ZERO);
	if (dup->functions == NULL)
		goto err_free;
	active = num_counter_active(info);
	fi_size = sizeof(struct gcov_fn_info);
	fi_size += sizeof(struct gcov_ctr_info) * active;

	for (fi_idx = 0; fi_idx < info->n_functions; fi_idx++) {
		dup->functions[fi_idx] = malloc(fi_size, M_GCOV, M_NOWAIT|M_ZERO);
		if (!dup->functions[fi_idx])
			goto err_free;

		*(dup->functions[fi_idx]) = *(info->functions[fi_idx]);

		sci_ptr = info->functions[fi_idx]->ctrs;
		dci_ptr = dup->functions[fi_idx]->ctrs;

		for (ct_idx = 0; ct_idx < active; ct_idx++) {

			cv_size = sizeof(gcov_type) * sci_ptr->num;

			dci_ptr->values = malloc(cv_size, M_GCOV, M_NOWAIT);

			if (!dci_ptr->values)
				goto err_free;

			dci_ptr->num = sci_ptr->num;
			memcpy(dci_ptr->values, sci_ptr->values, cv_size);

			sci_ptr++;
			dci_ptr++;
		}
	}

	return (dup);
err_free:
	gcov_info_free(dup);
	return (NULL);
}