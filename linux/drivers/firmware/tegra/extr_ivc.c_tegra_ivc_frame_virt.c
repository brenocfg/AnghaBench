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
struct tegra_ivc_header {int dummy; } ;
struct tegra_ivc {unsigned int num_frames; unsigned int frame_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void *tegra_ivc_frame_virt(struct tegra_ivc *ivc,
				  struct tegra_ivc_header *header,
				  unsigned int frame)
{
	if (WARN_ON(frame >= ivc->num_frames))
		return ERR_PTR(-EINVAL);

	return (void *)(header + 1) + ivc->frame_size * frame;
}