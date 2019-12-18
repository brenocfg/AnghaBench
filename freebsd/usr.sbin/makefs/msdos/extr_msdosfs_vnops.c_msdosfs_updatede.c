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
struct direntry {int dummy; } ;
struct denode {int /*<<< orphan*/  de_flag; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_EXTERNALIZE (struct direntry*,struct denode*) ; 
 int /*<<< orphan*/  DE_MODIFIED ; 
 int bwrite (struct buf*) ; 
 int readde (struct denode*,struct buf**,struct direntry**) ; 

__attribute__((used)) static int
msdosfs_updatede(struct denode *dep)
{
	struct buf *bp;
	struct direntry *dirp;
	int error;

	dep->de_flag &= ~DE_MODIFIED;
	error = readde(dep, &bp, &dirp);
	if (error)
		return error;
	DE_EXTERNALIZE(dirp, dep);
	error = bwrite(bp);
	return error;
}