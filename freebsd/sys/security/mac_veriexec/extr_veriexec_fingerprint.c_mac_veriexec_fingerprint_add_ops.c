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
struct mac_veriexec_fpops {char* type; scalar_t__ digest_len; scalar_t__ context_size; int /*<<< orphan*/ * final; int /*<<< orphan*/ * update; int /*<<< orphan*/ * init; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mac_veriexec_fpops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  fpops_list ; 
 scalar_t__ mac_veriexec_fingerprint_lookup_ops (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
mac_veriexec_fingerprint_add_ops(struct mac_veriexec_fpops *fpops)
{

	/* Sanity check the ops */
	if (fpops->type == NULL || fpops->digest_len == 0 ||
	    fpops->context_size == 0 || fpops->init == NULL ||
	    fpops->update == NULL || fpops->final == NULL)
		return (EINVAL);

	/* Make sure we do not already have ops for this digest type */
	if (mac_veriexec_fingerprint_lookup_ops(fpops->type))
		return (EEXIST);

	/* Add the ops to the list */
	LIST_INSERT_HEAD(&fpops_list, fpops, entries);

	printf("MAC/veriexec fingerprint module loaded: %s\n", fpops->type);

	return (0);
}