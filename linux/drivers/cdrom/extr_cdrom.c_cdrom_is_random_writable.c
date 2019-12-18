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
struct rwrt_feature_desc {int /*<<< orphan*/  feature_code; } ;
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ CDF_RWRT ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int cdrom_get_random_writable (struct cdrom_device_info*,struct rwrt_feature_desc*) ; 

__attribute__((used)) static int cdrom_is_random_writable(struct cdrom_device_info *cdi, int *write)
{
	struct rwrt_feature_desc rfd;
	int ret;

	*write = 0;

	if ((ret = cdrom_get_random_writable(cdi, &rfd)))
		return ret;

	if (CDF_RWRT == be16_to_cpu(rfd.feature_code))
		*write = 1;

	return 0;
}