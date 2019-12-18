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
struct testvec {int blkno; int /*<<< orphan*/  ctxt; } ;

/* Variables and functions */
 int SECSIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 char* malloc (int) ; 
 int memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int
check_testvec(int dkfd, const struct testvec *tv)
{
	char *buf;
	int res = -1;

	buf = malloc(SECSIZE);
	if (buf == NULL)
		return -1;

	if (lseek(dkfd, tv->blkno * SECSIZE, SEEK_SET) < 0)
		goto fail;

	if (read(dkfd, buf, SECSIZE) != SECSIZE)
		goto fail;

	res = memcmp(buf, tv->ctxt, SECSIZE);
fail:
	free(buf);
	return res;
}