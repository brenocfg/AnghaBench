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
struct entry {size_t e_ino; struct entry* e_next; } ;
typedef  size_t ino_t ;

/* Variables and functions */
 size_t UFS_WINO ; 
 struct entry** entry ; 
 size_t entrytblsize ; 
 size_t maxino ; 

struct entry *
lookupino(ino_t inum)
{
	struct entry *ep;

	if (inum < UFS_WINO || inum >= maxino)
		return (NULL);
	for (ep = entry[inum % entrytblsize]; ep != NULL; ep = ep->e_next)
		if (ep->e_ino == inum)
			return (ep);
	return (NULL);
}