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
struct kinfo_proc {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_PROC_PID ; 
 int /*<<< orphan*/  KVM_NO_FILES ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ *) ; 
 char** kvm_getenvv (int /*<<< orphan*/ *,struct kinfo_proc*,int /*<<< orphan*/ ) ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/ * kvm_openfiles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 char* xMalloc (size_t) ; 
 char* xRealloc (char*,size_t) ; 

char* Platform_getProcessEnv(pid_t pid) {
   char errbuf[_POSIX2_LINE_MAX];
   char *env;
   char **ptr;
   int count;
   kvm_t *kt;
   struct kinfo_proc *kproc;
   size_t capacity = 4096, size = 0;

   if ((kt = kvm_openfiles(NULL, NULL, NULL, KVM_NO_FILES, errbuf)) == NULL)
      return NULL;

   if ((kproc = kvm_getprocs(kt, KERN_PROC_PID, pid,
                             sizeof(struct kinfo_proc), &count)) == NULL) {\
      (void) kvm_close(kt);
      return NULL;
   }

   if ((ptr = kvm_getenvv(kt, kproc, 0)) == NULL) {
      (void) kvm_close(kt);
      return NULL;
   }

   env = xMalloc(capacity);
   for (char **p = ptr; *p; p++) {
      size_t len = strlen(*p) + 1;

      if (size + len > capacity) {
         capacity *= 2;
         env = xRealloc(env, capacity);
      }

      strlcpy(env + size, *p, len);
      size += len;
   }

   if (size < 2 || env[size - 1] || env[size - 2]) {
       if (size + 2 < capacity)
           env = xRealloc(env, capacity + 2);
       env[size] = 0;
       env[size+1] = 0;
   }

   (void) kvm_close(kt);
   return env;
}