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
struct arm64_image_header {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_IMAGE_MAGIC ; 
 int EINVAL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int image_probe(const char *kernel_buf, unsigned long kernel_len)
{
	const struct arm64_image_header *h =
		(const struct arm64_image_header *)(kernel_buf);

	if (!h || (kernel_len < sizeof(*h)))
		return -EINVAL;

	if (memcmp(&h->magic, ARM64_IMAGE_MAGIC, sizeof(h->magic)))
		return -EINVAL;

	return 0;
}