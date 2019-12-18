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
struct nvme_completion {int dummy; } ;
struct bio {struct bio* bio_parent; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  nvme_bio_child_inbed (struct bio*,int) ; 
 scalar_t__ nvme_completion_is_error (struct nvme_completion const*) ; 

__attribute__((used)) static void
nvme_bio_child_done(void *arg, const struct nvme_completion *cpl)
{
	struct bio		*child = arg;
	struct bio		*parent;
	int			bio_error;

	parent = child->bio_parent;
	g_destroy_bio(child);
	bio_error = nvme_completion_is_error(cpl) ? EIO : 0;
	nvme_bio_child_inbed(parent, bio_error);
}