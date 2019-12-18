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
typedef  int uint64_t ;
struct nvme_namespace {int dummy; } ;

/* Variables and functions */
 int nvme_ns_get_num_sectors (struct nvme_namespace*) ; 
 int nvme_ns_get_sector_size (struct nvme_namespace*) ; 

uint64_t
nvme_ns_get_size(struct nvme_namespace *ns)
{
	return (nvme_ns_get_num_sectors(ns) * nvme_ns_get_sector_size(ns));
}