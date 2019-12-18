#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fbtp_patchpoint; struct TYPE_6__* fbtp_tracenext; struct TYPE_6__* fbtp_hashnext; } ;
typedef  TYPE_1__ fbt_probe_t ;

/* Variables and functions */
 int FBT_ADDR2NDX (scalar_t__) ; 
 int /*<<< orphan*/  M_FBT ; 
 TYPE_1__** fbt_probetab ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 

__attribute__((used)) static void
fbt_destroy_one(fbt_probe_t *fbt)
{
	fbt_probe_t *hash, *hashprev, *next;
	int ndx;

	ndx = FBT_ADDR2NDX(fbt->fbtp_patchpoint);
	for (hash = fbt_probetab[ndx], hashprev = NULL; hash != NULL;
	    hashprev = hash, hash = hash->fbtp_hashnext) {
		if (hash == fbt) {
			if ((next = fbt->fbtp_tracenext) != NULL)
				next->fbtp_hashnext = hash->fbtp_hashnext;
			else
				next = hash->fbtp_hashnext;
			if (hashprev != NULL)
				hashprev->fbtp_hashnext = next;
			else
				fbt_probetab[ndx] = next;
			goto free;
		} else if (hash->fbtp_patchpoint == fbt->fbtp_patchpoint) {
			for (next = hash; next->fbtp_tracenext != NULL;
			    next = next->fbtp_tracenext) {
				if (fbt == next->fbtp_tracenext) {
					next->fbtp_tracenext =
					    fbt->fbtp_tracenext;
					goto free;
				}
			}
		}
	}
	panic("probe %p not found in hash table", fbt);
free:
	free(fbt, M_FBT);
}