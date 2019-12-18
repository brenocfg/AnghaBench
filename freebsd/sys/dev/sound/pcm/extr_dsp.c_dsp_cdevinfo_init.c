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
 int DSP_CDEVINFO_CACHESIZE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCM_BUSYASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  PCM_UNLOCKASSERT (struct snddev_info*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct dsp_cdevinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct dsp_cdevinfo* malloc (int,int /*<<< orphan*/ ,int) ; 

void
dsp_cdevinfo_init(struct snddev_info *d)
{
	struct dsp_cdevinfo *cdi;
	int i;

	KASSERT(d != NULL, ("NULL snddev_info"));
	PCM_BUSYASSERT(d);
	PCM_UNLOCKASSERT(d);

	TAILQ_INIT(&d->dsp_cdevinfo_pool);
	for (i = 0; i < DSP_CDEVINFO_CACHESIZE; i++) {
		cdi = malloc(sizeof(*cdi), M_DEVBUF, M_WAITOK | M_ZERO);
		TAILQ_INSERT_HEAD(&d->dsp_cdevinfo_pool, cdi, link);
	}
}