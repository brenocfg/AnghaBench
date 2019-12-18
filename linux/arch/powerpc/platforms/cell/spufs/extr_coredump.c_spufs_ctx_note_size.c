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
struct spu_context {int dummy; } ;
struct elf_note {int dummy; } ;
struct TYPE_2__ {char* name; int size; } ;

/* Variables and functions */
 scalar_t__ roundup (int,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 TYPE_1__* spufs_coredump_read ; 
 int strlen (char*) ; 

__attribute__((used)) static int spufs_ctx_note_size(struct spu_context *ctx, int dfd)
{
	int i, sz, total = 0;
	char *name;
	char fullname[80];

	for (i = 0; spufs_coredump_read[i].name != NULL; i++) {
		name = spufs_coredump_read[i].name;
		sz = spufs_coredump_read[i].size;

		sprintf(fullname, "SPU/%d/%s", dfd, name);

		total += sizeof(struct elf_note);
		total += roundup(strlen(fullname) + 1, 4);
		total += roundup(sz, 4);
	}

	return total;
}