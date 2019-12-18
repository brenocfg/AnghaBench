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
struct ib_pd {int dummy; } ;
struct ib_device {int dummy; } ;
struct fast_reg_descriptor {int /*<<< orphan*/  rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_ERR (char*) ; 
 int /*<<< orphan*/  M_ISER_VERBS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct fast_reg_descriptor*,int /*<<< orphan*/ ) ; 
 int iser_alloc_reg_res (struct ib_device*,struct ib_pd*,int /*<<< orphan*/ *) ; 
 struct fast_reg_descriptor* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct fast_reg_descriptor *
iser_create_fastreg_desc(struct ib_device *ib_device, struct ib_pd *pd)
{
	struct fast_reg_descriptor *desc;
	int ret;

	desc = malloc(sizeof(*desc), M_ISER_VERBS, M_WAITOK | M_ZERO);
	if (!desc) {
		ISER_ERR("Failed to allocate a new fastreg descriptor");
		return (NULL);
	}

	ret = iser_alloc_reg_res(ib_device, pd, &desc->rsc);
	if (ret) {
		ISER_ERR("failed to allocate reg_resources");
		goto err;
	}

	return (desc);
err:
	free(desc, M_ISER_VERBS);
	return (NULL);
}