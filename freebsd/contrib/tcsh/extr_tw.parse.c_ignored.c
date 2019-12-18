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
 int /*<<< orphan*/  STRfignore ; 
 int TRUE ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ is_suffix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ignored(Char *item)
{
    struct varent *vp;
    Char **cp;

    if ((vp = adrof(STRfignore)) == NULL || (cp = vp->vec) == NULL)
	return (FALSE);
    for (; *cp != NULL; cp++)
	if (is_suffix(item, *cp))
	    return (TRUE);
    return (FALSE);
}