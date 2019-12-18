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
struct secashead_queue {int dummy; } ;
struct secasvar {struct secashead_queue savtree_alive; struct secashead_queue savtree_larval; } ;
struct secashead {struct secashead_queue savtree_alive; struct secashead_queue savtree_larval; } ;

/* Variables and functions */
 struct secasvar* TAILQ_FIRST (struct secashead_queue*) ; 
 struct secasvar* TAILQ_NEXT (struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct secashead_queue*,struct secasvar*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  key_freesah (struct secasvar**) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar**) ; 

__attribute__((used)) static void
key_freesah_flushed(struct secashead_queue *flushq)
{
	struct secashead *sah, *nextsah;
	struct secasvar *sav, *nextsav;

	sah = TAILQ_FIRST(flushq);
	while (sah != NULL) {
		sav = TAILQ_FIRST(&sah->savtree_larval);
		while (sav != NULL) {
			nextsav = TAILQ_NEXT(sav, chain);
			TAILQ_REMOVE(&sah->savtree_larval, sav, chain);
			key_freesav(&sav); /* release last reference */
			key_freesah(&sah); /* release reference from SAV */
			sav = nextsav;
		}
		sav = TAILQ_FIRST(&sah->savtree_alive);
		while (sav != NULL) {
			nextsav = TAILQ_NEXT(sav, chain);
			TAILQ_REMOVE(&sah->savtree_alive, sav, chain);
			key_freesav(&sav); /* release last reference */
			key_freesah(&sah); /* release reference from SAV */
			sav = nextsav;
		}
		nextsah = TAILQ_NEXT(sah, chain);
		key_freesah(&sah);	/* release last reference */
		sah = nextsah;
	}
}