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
struct inodesc {int /*<<< orphan*/  id_parent; int /*<<< orphan*/  id_name; struct direct* id_dirp; } ;
struct direct {int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_ino; scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  ino_type; } ;

/* Variables and functions */
 int ALTERED ; 
 int KEEPON ; 
 int STOP ; 
 TYPE_1__* inoinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
chgino(struct inodesc *idesc)
{
	struct direct *dirp = idesc->id_dirp;

	if (memcmp(dirp->d_name, idesc->id_name, (int)dirp->d_namlen + 1))
		return (KEEPON);
	dirp->d_ino = idesc->id_parent;
	dirp->d_type = inoinfo(idesc->id_parent)->ino_type;
	return (ALTERED|STOP);
}