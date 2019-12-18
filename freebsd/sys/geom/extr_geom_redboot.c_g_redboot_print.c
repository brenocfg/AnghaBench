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
struct fis_image_desc {char* name; int offset; int size; int addr; int entry; int dsize; int dsum; int fsum; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
g_redboot_print(int i, struct fis_image_desc *fd)
{

	printf("[%2d] \"%-15.15s\" %08x:%08x", i, fd->name,
	    fd->offset, fd->size);
	printf(" addr %08x entry %08x\n", fd->addr, fd->entry);
	printf("     dsize 0x%x dsum 0x%x fsum 0x%x\n", fd->dsize,
	    fd->dsum, fd->fsum);
}