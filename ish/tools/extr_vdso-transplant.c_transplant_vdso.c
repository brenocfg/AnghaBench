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
typedef  int /*<<< orphan*/  line ;
typedef  scalar_t__ dword_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AX_SYSINFO ; 
 int /*<<< orphan*/  AX_SYSINFO_EHDR ; 
 int /*<<< orphan*/  PTRACE_POKEDATA ; 
 int /*<<< orphan*/  aux_write (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*,scalar_t__*,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

void transplant_vdso(int pid, const void *new_vdso, size_t new_vdso_size) {
    // get the vdso address and size from /proc/pid/maps
    char maps_file[32];
    sprintf(maps_file, "/proc/%d/maps", pid);
    FILE *maps = fopen(maps_file, "r");

    char line[256];
    dword_t start, end;
    while (fgets(line, sizeof(line), maps) != NULL) {
        char *map_type = NULL;
        sscanf(line, "%8x-%8x %*s %*s %*s %*s %ms\n", &start, &end, &map_type);
        if (map_type) {
            if (strcmp(map_type, "[vdso]") == 0) {
                free(map_type);
                break;
            }
            free(map_type);
        }
    }
    fclose(maps);

    // copy the new vdso in
    for (dword_t addr = start; addr < end; addr += sizeof(unsigned long)) {
        unsigned long new_vdso_data = 0;
        if (addr - start < new_vdso_size) {
            new_vdso_data = *(unsigned long *) ((char *) new_vdso + addr - start);
        }
        if (ptrace(PTRACE_POKEDATA, pid, addr, new_vdso_data) < 0) {
            perror("ptrace vdso poke"); exit(1);
        }
    }

    // find the entry point
    dword_t entry = *(dword_t *) ((char *) new_vdso + 24) + start;

    aux_write(pid, AX_SYSINFO, entry);
    aux_write(pid, AX_SYSINFO_EHDR, start);
}