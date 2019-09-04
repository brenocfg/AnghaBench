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
struct kinfo_proc2 {int p_vm_rssize; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_PROC_PID ; 
 int /*<<< orphan*/  KVM_NO_FILES ; 
 int UV_EPERM ; 
 int getpagesize () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ *) ; 
 struct kinfo_proc2* kvm_getproc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/ * kvm_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int uv_resident_set_memory(size_t* rss) {
  kvm_t *kd = NULL;
  struct kinfo_proc2 *kinfo = NULL;
  pid_t pid;
  int nprocs;
  int max_size = sizeof(struct kinfo_proc2);
  int page_size;

  page_size = getpagesize();
  pid = getpid();

  kd = kvm_open(NULL, NULL, NULL, KVM_NO_FILES, "kvm_open");

  if (kd == NULL) goto error;

  kinfo = kvm_getproc2(kd, KERN_PROC_PID, pid, max_size, &nprocs);
  if (kinfo == NULL) goto error;

  *rss = kinfo->p_vm_rssize * page_size;

  kvm_close(kd);

  return 0;

error:
  if (kd) kvm_close(kd);
  return UV_EPERM;
}