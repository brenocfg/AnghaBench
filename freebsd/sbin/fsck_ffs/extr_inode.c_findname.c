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
struct inodesc {scalar_t__ id_parent; int id_entryno; int /*<<< orphan*/  id_name; struct direct* id_dirp; } ;
struct direct {scalar_t__ d_ino; scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int FOUND ; 
 int KEEPON ; 
 int STOP ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int
findname(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;

	if (dirp->d_ino != idesc->id_parent || idesc->id_entryno < 2) {
		idesc->id_entryno++;
		return (KEEPON);
	}
	memmove(idesc->id_name, dirp->d_name, (size_t)dirp->d_namlen + 1);
	return (STOP|FOUND);
}