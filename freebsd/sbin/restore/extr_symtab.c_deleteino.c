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
typedef  int /*<<< orphan*/  uintmax_t ;
struct entry {size_t e_ino; struct entry* e_next; } ;
typedef  size_t ino_t ;

/* Variables and functions */
 size_t UFS_WINO ; 
 struct entry** entry ; 
 size_t entrytblsize ; 
 size_t maxino ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

void
deleteino(ino_t inum)
{
	struct entry *next;
	struct entry **prev;

	if (inum < UFS_WINO || inum >= maxino)
		panic("deleteino: out of range %ju\n", (uintmax_t)inum);
	prev = &entry[inum % entrytblsize];
	for (next = *prev; next != NULL; next = next->e_next) {
		if (next->e_ino == inum) {
			next->e_ino = 0;
			*prev = next->e_next;
			return;
		}
		prev = &next->e_next;
	}
	panic("deleteino: %ju not found\n", (uintmax_t)inum);
}