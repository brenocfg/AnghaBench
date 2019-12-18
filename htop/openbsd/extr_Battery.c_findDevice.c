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
struct sensordev {int /*<<< orphan*/  xname; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENXIO ; 
 scalar_t__ errno ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,struct sensordev*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool findDevice(const char* name, int* mib, struct sensordev* snsrdev, size_t* sdlen) {
   for (int devn = 0;; devn++) {
      mib[2] = devn;
      if (sysctl(mib, 3, snsrdev, sdlen, NULL, 0) == -1) {
         if (errno == ENXIO)
            continue;
         if (errno == ENOENT)
            return false;
      }
      if (strcmp(name, snsrdev->xname) == 0) {
         return true;
      }
   }
}