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
struct TYPE_2__ {int* fs_id; } ;

/* Variables and functions */
 char* _PATH_DEV ; 
 TYPE_1__ afs ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

__attribute__((used)) static int
dumpfsid(void)
{

	printf("%sufsid/%08x%08x\n", _PATH_DEV, afs.fs_id[0], afs.fs_id[1]);
	return 0;
}