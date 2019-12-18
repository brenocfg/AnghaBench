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
struct aac_softc {scalar_t__ total_fibs; scalar_t__ aac_max_fibs; int /*<<< orphan*/  aifthread; int /*<<< orphan*/  aifflags; } ;
struct aac_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_AIFFLAGS_ALLOCFIBS ; 
 int EBUSY ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 struct aac_command* aac_dequeue_free (struct aac_softc*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
aacraid_alloc_command(struct aac_softc *sc, struct aac_command **cmp)
{
	struct aac_command *cm;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if ((cm = aac_dequeue_free(sc)) == NULL) {
		if (sc->total_fibs < sc->aac_max_fibs) {
			sc->aifflags |= AAC_AIFFLAGS_ALLOCFIBS;
			wakeup(sc->aifthread);
		}
		return (EBUSY);
	}

	*cmp = cm;
	return(0);
}