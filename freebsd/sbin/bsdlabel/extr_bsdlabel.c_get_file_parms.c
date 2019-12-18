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
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_BSIZE ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  mediasize ; 
 int /*<<< orphan*/  secsize ; 
 int /*<<< orphan*/  specname ; 

__attribute__((used)) static void
get_file_parms(int f)
{
	int i;
	struct stat sb;

	if (fstat(f, &sb) != 0)
		err(4, "fstat failed");
	i = sb.st_mode & S_IFMT;
	if (i != S_IFREG && i != S_IFLNK)
		errx(4, "%s is not a valid file or link", specname);
	secsize = DEV_BSIZE;
	mediasize = sb.st_size;
}