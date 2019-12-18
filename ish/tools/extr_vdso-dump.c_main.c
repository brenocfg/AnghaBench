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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYSINFO_EHDR ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ getauxval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int main() {
    void *vdso = (void *) getauxval(AT_SYSINFO_EHDR);
    FILE *f = fopen("libvdso.so", "w");
    if (f == NULL) {
        perror("fopen libvdso.so");
        return 1;
    }
    fwrite(vdso, 0x2000, 1, f);
}