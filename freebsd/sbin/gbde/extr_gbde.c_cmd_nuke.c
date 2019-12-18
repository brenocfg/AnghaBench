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
typedef  int /*<<< orphan*/  u_char ;
struct g_bde_key {int* lsector; scalar_t__ sectorsize; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int write (int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
cmd_nuke(struct g_bde_key *gl, int dfd , int key)
{
	int i;
	u_char *sbuf;
	off_t offset, offset2;

	sbuf = malloc(gl->sectorsize);
	memset(sbuf, 0, gl->sectorsize);
	offset = (gl->lsector[key] & ~(gl->sectorsize - 1));
	offset2 = lseek(dfd, offset, SEEK_SET);
	if (offset2 != offset)
		err(1, "lseek");
	i = write(dfd, sbuf, gl->sectorsize);
	free(sbuf);
	if (i != (int)gl->sectorsize)
		err(1, "write");
	printf("Nuked key %d\n", 1 + key);
}