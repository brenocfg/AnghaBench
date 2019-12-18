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

/* Variables and functions */
 int /*<<< orphan*/  STRsavedirs ; 
 int /*<<< orphan*/  STRsavehist ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  displayHistStats (char*) ; 
 int /*<<< orphan*/  fast ; 
 int /*<<< orphan*/  recdirs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rechist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
record(void)
{
    if (!fast) {
	recdirs(NULL, adrof(STRsavedirs) != NULL);
	rechist(NULL, adrof(STRsavehist) != NULL);
    }
    displayHistStats("Exiting");	/* no-op unless DEBUG_HIST */
}