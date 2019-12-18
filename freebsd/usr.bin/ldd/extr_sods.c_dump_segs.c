#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ d_sdt; } ;
struct TYPE_6__ {TYPE_1__ d_un; scalar_t__ d_debug; } ;
struct TYPE_5__ {unsigned long sdt_rel; unsigned long sdt_hash; unsigned long sdt_nzlist; unsigned long sdt_strings; unsigned long sdt_got; unsigned long sdt_plt; unsigned long sdt_plt_sz; } ;

/* Variables and functions */
 int EX_DYNAMIC ; 
 unsigned long N_DATOFF (int /*<<< orphan*/ ) ; 
 int N_GETFLAG (int /*<<< orphan*/ ) ; 
 unsigned long N_TXTOFF (int /*<<< orphan*/ ) ; 
 TYPE_3__* dyn ; 
 int /*<<< orphan*/ * ex ; 
 unsigned long origin ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 TYPE_2__* sdt ; 

__attribute__((used)) static void
dump_segs(void)
{
    printf("  Text segment starts at address %lx\n", origin + N_TXTOFF(*ex));
    if (N_GETFLAG(*ex) & EX_DYNAMIC) {
	printf("    rel starts at %lx\n", sdt->sdt_rel);
	printf("    hash starts at %lx\n", sdt->sdt_hash);
	printf("    nzlist starts at %lx\n", sdt->sdt_nzlist);
	printf("    strings starts at %lx\n", sdt->sdt_strings);
    }

    printf("  Data segment starts at address %lx\n", origin + N_DATOFF(*ex));
    if (N_GETFLAG(*ex) & EX_DYNAMIC) {
	printf("    _dynamic starts at %lx\n", origin + N_DATOFF(*ex));
	printf("    so_debug starts at %lx\n", (unsigned long) dyn->d_debug);
	printf("    sdt starts at %lx\n", (unsigned long) dyn->d_un.d_sdt);
	printf("    got starts at %lx\n", sdt->sdt_got);
	printf("    plt starts at %lx\n", sdt->sdt_plt);
	printf("    rest of stuff starts at %lx\n",
	    sdt->sdt_plt + sdt->sdt_plt_sz);
    }
}