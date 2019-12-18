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
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int D_TAPE ; 
 int /*<<< orphan*/  FIODTYPE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  address ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  noseek () ; 
 scalar_t__ skip ; 
 int /*<<< orphan*/  stdin ; 

void
doskip(const char *fname, int statok)
{
	int type;
	struct stat sb;

	if (statok) {
		if (fstat(fileno(stdin), &sb))
			err(1, "%s", fname);
		if (S_ISREG(sb.st_mode) && skip > sb.st_size) {
			address += sb.st_size;
			skip -= sb.st_size;
			return;
		}
	}
	if (!statok || S_ISFIFO(sb.st_mode) || S_ISSOCK(sb.st_mode)) {
		noseek();
		return;
	}
	if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) {
		if (ioctl(fileno(stdin), FIODTYPE, &type))
			err(1, "%s", fname);
		/*
		 * Most tape drives don't support seeking,
		 * yet fseek() would succeed.
		 */
		if (type & D_TAPE) {
			noseek();
			return;
		}
	}
	if (fseeko(stdin, skip, SEEK_SET)) {
		noseek();
		return;
	}
	address += skip;
	skip = 0;
}