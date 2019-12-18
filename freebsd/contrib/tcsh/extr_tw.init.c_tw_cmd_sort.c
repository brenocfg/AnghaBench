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
struct TYPE_2__ {size_t nlist; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 scalar_t__ Strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disabled_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcompare ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ tw_cmd ; 

__attribute__((used)) static void
tw_cmd_sort(void)
{
    size_t fwd, i;

    pintr_disabled++;
    /* sort the list. */
    qsort(tw_cmd.list, tw_cmd.nlist, sizeof(Char *), fcompare);

    /* get rid of multiple entries */
    for (i = 0, fwd = 0; i + 1 < tw_cmd.nlist; i++) {
	if (Strcmp(tw_cmd.list[i], tw_cmd.list[i + 1]) == 0) /* garbage */
	    fwd++;		/* increase the forward ref. count */
	else if (fwd) 
	    tw_cmd.list[i - fwd] = tw_cmd.list[i];
    }
    /* Fix fencepost error -- Theodore Ts'o <tytso@athena.mit.edu> */
    if (fwd)
	tw_cmd.list[i - fwd] = tw_cmd.list[i];
    tw_cmd.nlist -= fwd;
    disabled_cleanup(&pintr_disabled);
}