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
struct stat {int st_size; } ;
struct quotafile {int wordsize; int /*<<< orphan*/  qfname; } ;
struct dqblk64 {int dummy; } ;
struct dqblk32 {int dummy; } ;

/* Variables and functions */
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

int
quota_maxid(struct quotafile *qf)
{
	struct stat st;
	int maxid;

	if (stat(qf->qfname, &st) < 0)
		return (0);
	switch (qf->wordsize) {
	case 32:
		maxid = st.st_size / sizeof(struct dqblk32) - 1;
		break;
	case 64:
		maxid = st.st_size / sizeof(struct dqblk64) - 2;
		break;
	default:
		maxid = 0;
		break;
	}
	return (maxid > 0 ? maxid : 0);
}