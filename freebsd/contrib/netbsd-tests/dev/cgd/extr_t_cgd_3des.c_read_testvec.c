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
struct testvec {int blkno; int /*<<< orphan*/  ptxt; } ;

/* Variables and functions */
 int SECSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int memcmp (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rump_sys_lseek (int,int,int /*<<< orphan*/ ) ; 
 int rump_sys_read (int,char*,int) ; 

__attribute__((used)) static int
read_testvec(int cgdfd, const struct testvec *tv)
{
	char *buf;
	int res = -1;

	buf = malloc(SECSIZE);
	if (buf == NULL)
		return -1;

	if (rump_sys_lseek(cgdfd, tv->blkno * SECSIZE, SEEK_SET) < 0)
		goto fail;

	if (rump_sys_read(cgdfd, buf, SECSIZE) != SECSIZE)
		goto fail;

	res = memcmp(buf, tv->ptxt, SECSIZE);
fail:
	free(buf);
	return res;
}