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
typedef  size_t uint32_t ;
struct nvme_namespace {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nn; } ;
struct nvme_controller {struct nvme_namespace* ns; TYPE_1__ cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_MAX_NAMESPACES ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ns_construct (struct nvme_namespace*,size_t,struct nvme_controller*) ; 

__attribute__((used)) static int
nvme_ctrlr_construct_namespaces(struct nvme_controller *ctrlr)
{
	struct nvme_namespace	*ns;
	uint32_t 		i;

	for (i = 0; i < min(ctrlr->cdata.nn, NVME_MAX_NAMESPACES); i++) {
		ns = &ctrlr->ns[i];
		nvme_ns_construct(ns, i+1, ctrlr);
	}

	return (0);
}