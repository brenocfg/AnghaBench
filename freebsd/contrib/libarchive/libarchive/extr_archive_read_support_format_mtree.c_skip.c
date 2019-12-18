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
struct mtree {int fd; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static int
skip(struct archive_read *a)
{
	struct mtree *mtree;

	mtree = (struct mtree *)(a->format->data);
	if (mtree->fd >= 0) {
		close(mtree->fd);
		mtree->fd = -1;
	}
	return (ARCHIVE_OK);
}