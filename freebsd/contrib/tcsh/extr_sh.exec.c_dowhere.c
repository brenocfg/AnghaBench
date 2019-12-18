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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  STR1 ; 
 int /*<<< orphan*/  STRautorehash ; 
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int find_cmd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dowhere(Char **v, struct command *c)
{
    int found = 1;
    USE(c);

    if (adrof(STRautorehash))
	dohash(NULL, NULL);
    for (v++; *v; v++)
	found &= find_cmd(*v, 1);
    /* Make status nonzero if any command is not found. */
    if (!found)
	setcopy(STRstatus, STR1, VAR_READWRITE);
}