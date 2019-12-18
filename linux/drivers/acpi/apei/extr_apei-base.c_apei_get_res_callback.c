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
struct apei_resources {int /*<<< orphan*/  iomem; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int apei_res_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apei_get_res_callback(__u64 start, __u64 size, void *data)
{
	struct apei_resources *resources = data;
	return apei_res_add(&resources->iomem, start, size);
}