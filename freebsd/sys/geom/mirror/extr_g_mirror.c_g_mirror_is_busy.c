#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_mirror_softc {int dummy; } ;
struct g_consumer {scalar_t__ index; TYPE_1__* provider; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ g_mirror_nrequests (struct g_mirror_softc*,struct g_consumer*) ; 

__attribute__((used)) static int
g_mirror_is_busy(struct g_mirror_softc *sc, struct g_consumer *cp)
{

	if (cp->index > 0) {
		G_MIRROR_DEBUG(2,
		    "I/O requests for %s exist, can't destroy it now.",
		    cp->provider->name);
		return (1);
	}
	if (g_mirror_nrequests(sc, cp) > 0) {
		G_MIRROR_DEBUG(2,
		    "I/O requests for %s in queue, can't destroy it now.",
		    cp->provider->name);
		return (1);
	}
	return (0);
}