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
typedef  scalar_t__ uint64_t ;
struct virtio_feature_desc {scalar_t__ vfd_val; char const* vfd_str; } ;

/* Variables and functions */
 struct virtio_feature_desc* virtio_common_feature_desc ; 

__attribute__((used)) static const char *
virtio_feature_name(uint64_t val, struct virtio_feature_desc *desc)
{
	int i, j;
	struct virtio_feature_desc *descs[2] = { desc,
	    virtio_common_feature_desc };

	for (i = 0; i < 2; i++) {
		if (descs[i] == NULL)
			continue;

		for (j = 0; descs[i][j].vfd_val != 0; j++) {
			if (val == descs[i][j].vfd_val)
				return (descs[i][j].vfd_str);
		}
	}

	return (NULL);
}