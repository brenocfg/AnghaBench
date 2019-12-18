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
typedef  int /*<<< orphan*/  uint8_t ;
struct mps_softc {int pqdepth; int num_replies; int fqdepth; int replyframesz; int replyfreeindex; scalar_t__ reply_busaddr; scalar_t__* free_queue; scalar_t__ post_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
mps_init_queues(struct mps_softc *sc)
{
	int i;

	memset((uint8_t *)sc->post_queue, 0xff, sc->pqdepth * 8);

	/*
	 * According to the spec, we need to use one less reply than we
	 * have space for on the queue.  So sc->num_replies (the number we
	 * use) should be less than sc->fqdepth (allocated size).
	 */
	if (sc->num_replies >= sc->fqdepth)
		return (EINVAL);

	/*
	 * Initialize all of the free queue entries.
	 */
	for (i = 0; i < sc->fqdepth; i++)
		sc->free_queue[i] = sc->reply_busaddr + (i * sc->replyframesz);
	sc->replyfreeindex = sc->num_replies;

	return (0);
}