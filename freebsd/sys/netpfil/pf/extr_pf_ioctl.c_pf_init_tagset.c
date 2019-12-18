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
struct pf_tagset {unsigned int mask; int /*<<< orphan*/  avail; int /*<<< orphan*/ * taghash; int /*<<< orphan*/ * namehash; int /*<<< orphan*/  seed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_FILL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_PFHASH ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAGID_MAX ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc4random () ; 
 void* mallocarray (unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerof2 (unsigned int) ; 

__attribute__((used)) static void
pf_init_tagset(struct pf_tagset *ts, unsigned int *tunable_size,
    unsigned int default_size)
{
	unsigned int i;
	unsigned int hashsize;
	
	if (*tunable_size == 0 || !powerof2(*tunable_size))
		*tunable_size = default_size;

	hashsize = *tunable_size;
	ts->namehash = mallocarray(hashsize, sizeof(*ts->namehash), M_PFHASH,
	    M_WAITOK);
	ts->taghash = mallocarray(hashsize, sizeof(*ts->taghash), M_PFHASH,
	    M_WAITOK);
	ts->mask = hashsize - 1;
	ts->seed = arc4random();
	for (i = 0; i < hashsize; i++) {
		TAILQ_INIT(&ts->namehash[i]);
		TAILQ_INIT(&ts->taghash[i]);
	}
	BIT_FILL(TAGID_MAX, &ts->avail);
}