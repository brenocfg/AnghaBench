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
typedef  int u32 ;
struct mpc52xx_ata_timings {int mdma1; int mdma2; scalar_t__ using_udma; } ;
struct mpc52xx_ata_priv {struct mdmaspec* mdmaspec; struct mpc52xx_ata_timings* timings; } ;
struct mdmaspec {int tm; scalar_t__ tn; scalar_t__ tj; scalar_t__ th; scalar_t__ tkw; scalar_t__ td; scalar_t__ t0M; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mpc52xx_ata_compute_mdma_timings(struct mpc52xx_ata_priv *priv, int dev,
				 int speed)
{
	struct mpc52xx_ata_timings *t = &priv->timings[dev];
	const struct mdmaspec *s = &priv->mdmaspec[speed];

	if (speed < 0 || speed > 2)
		return -EINVAL;

	t->mdma1 = ((u32)s->t0M << 24) | ((u32)s->td << 16) | ((u32)s->tkw << 8) | s->tm;
	t->mdma2 = ((u32)s->th << 24) | ((u32)s->tj << 16) | ((u32)s->tn << 8);
	t->using_udma = 0;

	return 0;
}