#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  mtime; } ;
struct TYPE_4__ {TYPE_1__ a; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ SFTP_DIRENT ;

/* Variables and functions */
 int LS_NAME_SORT ; 
 int LS_REVERSE_SORT ; 
 int LS_SIZE_SORT ; 
 int LS_TIME_SORT ; 
 int NCMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int sort_flag ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sdirent_comp(const void *aa, const void *bb)
{
	SFTP_DIRENT *a = *(SFTP_DIRENT **)aa;
	SFTP_DIRENT *b = *(SFTP_DIRENT **)bb;
	int rmul = sort_flag & LS_REVERSE_SORT ? -1 : 1;

#define NCMP(a,b) (a == b ? 0 : (a < b ? 1 : -1))
	if (sort_flag & LS_NAME_SORT)
		return (rmul * strcmp(a->filename, b->filename));
	else if (sort_flag & LS_TIME_SORT)
		return (rmul * NCMP(a->a.mtime, b->a.mtime));
	else if (sort_flag & LS_SIZE_SORT)
		return (rmul * NCMP(a->a.size, b->a.size));

	fatal("Unknown ls sort type");
}