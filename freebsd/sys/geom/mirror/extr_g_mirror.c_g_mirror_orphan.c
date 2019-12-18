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
struct g_mirror_disk {TYPE_1__* d_softc; } ;
struct g_consumer {struct g_mirror_disk* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_bump_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_BUMP_SYNCID ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  G_MIRROR_EVENT_DONTWAIT ; 
 int /*<<< orphan*/  g_mirror_event_send (struct g_mirror_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_mirror_orphan(struct g_consumer *cp)
{
	struct g_mirror_disk *disk;

	g_topology_assert();

	disk = cp->private;
	if (disk == NULL)
		return;
	disk->d_softc->sc_bump_id |= G_MIRROR_BUMP_SYNCID;
	g_mirror_event_send(disk, G_MIRROR_DISK_STATE_DISCONNECTED,
	    G_MIRROR_EVENT_DONTWAIT);
}