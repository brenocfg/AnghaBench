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
struct snddev_info {int /*<<< orphan*/  dsp_cdevinfo_pool; } ;
struct dsp_cdevinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCKASSERT (struct snddev_info*) ; 
 struct dsp_cdevinfo* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct dsp_cdevinfo* TAILQ_NEXT (struct dsp_cdevinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct dsp_cdevinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

void
dsp_cdevinfo_flush(struct snddev_info *d)
{
	struct dsp_cdevinfo *cdi, *tmp;

	KASSERT(d != NULL, ("NULL snddev_info"));
	PCM_BUSYASSERT(d);
	PCM_UNLOCKASSERT(d);

	cdi = TAILQ_FIRST(&d->dsp_cdevinfo_pool);
	while (cdi != NULL) {
		tmp = TAILQ_NEXT(cdi, link);
		free(cdi, M_DEVBUF);
		cdi = tmp;
	}
	TAILQ_INIT(&d->dsp_cdevinfo_pool);
}