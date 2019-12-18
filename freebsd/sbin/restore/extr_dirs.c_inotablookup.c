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
struct inotab {scalar_t__ t_ino; struct inotab* t_next; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 size_t INOHASH (scalar_t__) ; 
 struct inotab** inotab ; 

__attribute__((used)) static struct inotab *
inotablookup(ino_t ino)
{
	struct inotab *itp;

	for (itp = inotab[INOHASH(ino)]; itp != NULL; itp = itp->t_next)
		if (itp->t_ino == ino)
			return (itp);
	return (NULL);
}