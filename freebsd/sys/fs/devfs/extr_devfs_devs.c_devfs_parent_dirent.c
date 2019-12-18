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
struct devfs_dirent {int de_flags; struct devfs_dirent* de_dir; int /*<<< orphan*/  de_dlist; TYPE_1__* de_dirent; } ;
struct TYPE_2__ {scalar_t__ d_type; } ;

/* Variables and functions */
 int DE_DOT ; 
 int DE_DOTDOT ; 
 scalar_t__ DT_DIR ; 
 struct devfs_dirent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct devfs_dirent* TAILQ_NEXT (struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_list ; 

struct devfs_dirent *
devfs_parent_dirent(struct devfs_dirent *de)
{

	if (de->de_dirent->d_type != DT_DIR)
		return (de->de_dir);

	if (de->de_flags & (DE_DOT | DE_DOTDOT))
		return (NULL);

	de = TAILQ_FIRST(&de->de_dlist);	/* "." */
	if (de == NULL)
		return (NULL);
	de = TAILQ_NEXT(de, de_list);		/* ".." */
	if (de == NULL)
		return (NULL);

	return (de->de_dir);
}