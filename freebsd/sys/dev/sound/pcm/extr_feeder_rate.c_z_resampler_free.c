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
struct z_info {struct z_info* z_delay; struct z_info* z_pcoeff; } ;
struct pcm_feeder {struct z_info* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct z_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
z_resampler_free(struct pcm_feeder *f)
{
	struct z_info *info;

	info = f->data;
	if (info != NULL) {
		if (info->z_pcoeff != NULL)
			free(info->z_pcoeff, M_DEVBUF);
		if (info->z_delay != NULL)
			free(info->z_delay, M_DEVBUF);
		free(info, M_DEVBUF);
	}

	f->data = NULL;

	return (0);
}