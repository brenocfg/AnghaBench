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
struct TYPE_2__ {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int close (int /*<<< orphan*/ ) ; 
 char* dbm_base ; 
 int /*<<< orphan*/  ifd ; 
 int munmap (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ st ; 
 int /*<<< orphan*/  warn (char*) ; 

void
dbm_unmap(void)
{
	if (munmap(dbm_base, st.st_size) == -1)
		warn("dbm_unmap: munmap");
	if (close(ifd) == -1)
		warn("dbm_unmap: close");
	dbm_base = (char *)-1;
}