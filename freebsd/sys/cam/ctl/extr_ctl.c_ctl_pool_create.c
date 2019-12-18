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
typedef  int /*<<< orphan*/  uint32_t ;
struct ctl_softc {int /*<<< orphan*/  io_zone; } ;
struct ctl_io_pool {int /*<<< orphan*/  zone; int /*<<< orphan*/  name; struct ctl_softc* ctl_softc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_CTL ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  uma_zsecond_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ctl_pool_create(struct ctl_softc *ctl_softc, const char *pool_name,
		uint32_t total_ctl_io, void **npool)
{
	struct ctl_io_pool *pool;

	pool = (struct ctl_io_pool *)malloc(sizeof(*pool), M_CTL,
					    M_NOWAIT | M_ZERO);
	if (pool == NULL)
		return (ENOMEM);

	snprintf(pool->name, sizeof(pool->name), "CTL IO %s", pool_name);
	pool->ctl_softc = ctl_softc;
#ifdef IO_POOLS
	pool->zone = uma_zsecond_create(pool->name, NULL,
	    NULL, NULL, NULL, ctl_softc->io_zone);
	/* uma_prealloc(pool->zone, total_ctl_io); */
#else
	pool->zone = ctl_softc->io_zone;
#endif

	*npool = pool;
	return (0);
}