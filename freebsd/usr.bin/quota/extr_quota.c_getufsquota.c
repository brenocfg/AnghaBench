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
struct quotause {int /*<<< orphan*/  dqblk; } ;
struct quotafile {int dummy; } ;
struct fstab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  quota_close (struct quotafile*) ; 
 struct quotafile* quota_open (struct fstab*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ quota_read (struct quotafile*,int /*<<< orphan*/ *,long) ; 

__attribute__((used)) static int
getufsquota(struct fstab *fs, struct quotause *qup, long id, int quotatype)
{
	struct quotafile *qf;

	if ((qf = quota_open(fs, quotatype, O_RDONLY)) == NULL)
		return (0);
	if (quota_read(qf, &qup->dqblk, id) != 0)
		return (0);
	quota_close(qf);
	return (1);
}