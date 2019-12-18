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
typedef  int /*<<< orphan*/  dword_t ;
typedef  scalar_t__ addr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_read (int,scalar_t__) ; 

void dump_memory(int pid, const char *file, addr_t start, addr_t end) {
    FILE *f = fopen(file, "w");
    for (addr_t addr = start; addr <= end; addr += sizeof(dword_t)) {
        dword_t val = pt_read(pid, addr);
        fwrite(&val, sizeof(dword_t), 1, f);
    }
    fclose(f);
}