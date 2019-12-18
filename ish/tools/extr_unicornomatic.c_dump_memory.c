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
typedef  int /*<<< orphan*/  uc_engine ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uc_mem_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  uc_trycall (int /*<<< orphan*/ ,char*) ; 

void dump_memory(uc_engine *uc, const char *file, addr_t start, size_t size) {
    char buf[size];
    uc_trycall(uc_mem_read(uc, start, buf, size), "uc_mem_read");
    FILE *f = fopen(file, "w");
    fwrite(buf, 1, sizeof(buf), f);
    fclose(f);
}