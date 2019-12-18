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
struct stat {size_t st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int start_tracee (int /*<<< orphan*/ ,char* const,char* const*,char* const*) ; 
 int /*<<< orphan*/  transplant_vdso (int,void*,size_t) ; 
 int trycall (int /*<<< orphan*/ ,char*) ; 

int main(int argc, char *const argv[]) {
    char *const envp[] = {NULL};
    int pid = start_tracee(AT_FDCWD, argv[2], argv + 2, envp);

    int vdso_fd = trycall(open(argv[1], O_RDONLY), "open vdso");
    struct stat statbuf;
    trycall(fstat(vdso_fd, &statbuf), "stat vdso");
    size_t vdso_size = statbuf.st_size;
    void *vdso = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, vdso_fd, 0);
    if (vdso == MAP_FAILED) {
        perror("mmap vdso"); exit(1);
    }
    transplant_vdso(pid, vdso, vdso_size);

    trycall(kill(pid, SIGSTOP), "pause process");
    printf("attach debugger to %d\n", pid);
    return 0;
}