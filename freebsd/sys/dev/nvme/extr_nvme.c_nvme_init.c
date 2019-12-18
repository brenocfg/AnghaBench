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
struct nvme_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_CONSUMER_ID ; 
 size_t NVME_MAX_CONSUMERS ; 
 TYPE_1__* nvme_consumer ; 
 int /*<<< orphan*/  nvme_request_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nvme_init(void)
{
	uint32_t	i;

	nvme_request_zone = uma_zcreate("nvme_request",
	    sizeof(struct nvme_request), NULL, NULL, NULL, NULL, 0, 0);

	for (i = 0; i < NVME_MAX_CONSUMERS; i++)
		nvme_consumer[i].id = INVALID_CONSUMER_ID;
}