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
struct varent {int /*<<< orphan*/ ** vec; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ Gmatch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRnostat ; 
 int /*<<< orphan*/  STRstar ; 
 scalar_t__ Strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nostat(Char *dir)
{
    struct varent *vp;
    Char **cp;

    if ((vp = adrof(STRnostat)) == NULL || (cp = vp->vec) == NULL)
	return FALSE;
    for (; *cp != NULL; cp++) {
	if (Strcmp(*cp, STRstar) == 0)
	    return TRUE;
	if (Gmatch(dir, *cp))
	    return TRUE;
    }
    return FALSE;
}