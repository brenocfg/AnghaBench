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
struct denode {int /*<<< orphan*/  de_diroffset; int /*<<< orphan*/  de_dirclust; int /*<<< orphan*/  de_pmp; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int readep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**,struct direntry**) ; 

int
readde(struct denode *dep, struct buf **bpp, struct direntry **epp)
{

	return (readep(dep->de_pmp, dep->de_dirclust, dep->de_diroffset,
	    bpp, epp));
}