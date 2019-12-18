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
struct inodesc {int /*<<< orphan*/  id_parent; struct direct* id_dirp; } ;
struct direct {int /*<<< orphan*/  d_ino; } ;

/* Variables and functions */
 int ALTERED ; 
 int FOUND ; 
 int KEEPON ; 
 int STOP ; 
 scalar_t__ desired ; 
 int /*<<< orphan*/  slotcount ; 

int
chinumfunc(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;

	if (slotcount++ == desired) {
	    dirp->d_ino = idesc->id_parent;
	    return STOP|ALTERED|FOUND;
	}
	return KEEPON;
}