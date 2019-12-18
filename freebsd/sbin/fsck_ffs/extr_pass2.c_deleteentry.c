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
struct inodesc {scalar_t__ id_parent; int /*<<< orphan*/  id_entryno; struct direct* id_dirp; } ;
struct direct {scalar_t__ d_ino; } ;

/* Variables and functions */
 int ALTERED ; 
 int FOUND ; 
 int KEEPON ; 
 int STOP ; 

__attribute__((used)) static int
deleteentry(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;

	if (idesc->id_entryno++ < 2 || dirp->d_ino != idesc->id_parent)
		return (KEEPON);
	dirp->d_ino = 0;
	return (ALTERED|STOP|FOUND);
}