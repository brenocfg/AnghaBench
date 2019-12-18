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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  argmax ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_ARGMAX ; 
 int KERN_PROCARGS2 ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* strchr (char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,...) ; 
 char* xMalloc (size_t) ; 

char* Platform_getProcessEnv(pid_t pid) {
   char* env = NULL;

   int argmax;
   size_t bufsz = sizeof(argmax);

   int mib[3];
   mib[0] = CTL_KERN;
   mib[1] = KERN_ARGMAX;
   if (sysctl(mib, 2, &argmax, &bufsz, 0, 0) == 0) {
      char* buf = xMalloc(argmax);
      if (buf) {
         mib[0] = CTL_KERN;
         mib[1] = KERN_PROCARGS2;
         mib[2] = pid;
         size_t bufsz = argmax;
         if (sysctl(mib, 3, buf, &bufsz, 0, 0) == 0) {
            if (bufsz > sizeof(int)) {
               char *p = buf, *endp = buf + bufsz;
               int argc = *(int*)p;
               p += sizeof(int);

               // skip exe
               p = strchr(p, 0)+1;

               // skip padding
               while(!*p && p < endp)
                  ++p;

               // skip argv
               for (; argc-- && p < endp; p = strrchr(p, 0)+1)
                  ;

               // skip padding
               while(!*p && p < endp)
                  ++p;

               size_t size = endp - p;
               env = xMalloc(size+2);
               memcpy(env, p, size);
               env[size] = 0;
               env[size+1] = 0;
            }
         }
         free(buf);
      }
   }

   return env;
}