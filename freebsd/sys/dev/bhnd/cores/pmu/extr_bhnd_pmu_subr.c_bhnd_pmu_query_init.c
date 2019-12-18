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
struct bhnd_chipid {int dummy; } ;
struct bhnd_pmu_query {int /*<<< orphan*/  caps; struct bhnd_chipid cid; void* io_ctx; struct bhnd_pmu_io const* io; int /*<<< orphan*/  dev; } ;
struct bhnd_pmu_io {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_CAP ; 
 int /*<<< orphan*/  BHND_PMU_READ_4 (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 

int	
bhnd_pmu_query_init(struct bhnd_pmu_query *query, device_t dev,
    struct bhnd_chipid id, const struct bhnd_pmu_io *io, void *ctx)
{
	query->dev = dev;
	query->io = io;
	query->io_ctx = ctx;
	query->cid = id;
	query->caps = BHND_PMU_READ_4(query, BHND_PMU_CAP);

	return (0);
}