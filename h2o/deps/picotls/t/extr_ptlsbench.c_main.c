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
typedef  scalar_t__ uint64_t ;
struct utsname {int /*<<< orphan*/  machine; int /*<<< orphan*/  sysname; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  aead; int /*<<< orphan*/  algo_name; int /*<<< orphan*/  provider; } ;
typedef  int /*<<< orphan*/  OS ;
typedef  int /*<<< orphan*/  HW ;

/* Variables and functions */
 TYPE_1__* aead_list ; 
 int bench_basic (scalar_t__*) ; 
 int bench_run_aead (char*,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 
 size_t nb_aead_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy_s (char*,int,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ uname (struct utsname*) ; 

int main(int argc, char **argv)
{
    int ret = 0;
    uint64_t x = 0xdeadbeef;
    uint64_t s = 0;
    int basic_ref = bench_basic(&x);
    char OS[128];
    char HW[128];
#ifndef _WINDOWS
    struct utsname uts;
#endif

#ifdef _WINDOWS
    (void) strcpy_s(OS, sizeof(OS), "windows");
    (void)strcpy_s(HW, sizeof(HW), "x86_64");
#else
    OS[0] = 0;
    HW[0] = 0;
    if (uname(&uts) == 0) {
        if (strlen(uts.sysname) + 1 < sizeof(OS)){
            strcpy(OS, uts.sysname);
        }
        if (strlen(uts.machine) + 1 < sizeof(HW)){
            strcpy(HW, uts.machine);
        }
    }
#endif

    
    printf("OS, HW, bits, mode, 10M ops, provider, version, algorithm, N, L, encrypt us, decrypt us, encrypt mbps, decrypt mbps,\n");
    

    for (size_t i = 0; ret == 0 && i < nb_aead_list; i++) {
        ret = bench_run_aead(OS, HW, basic_ref, x, aead_list[i].provider, aead_list[i].algo_name, aead_list[i].aead, aead_list[i].hash, 1000,
                             1500, &s);
    }

    /* Gratuitous test, designed to ensure that the initial computation
     * of the basic reference benchmark is not optimised away. */
    if (s == 0){
       printf("Unexpected value of test sum s = %llx\n", (unsigned long long)s);
    } 

    return ret;
}