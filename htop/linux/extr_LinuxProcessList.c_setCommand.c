#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int commLen; scalar_t__ comm; } ;
typedef  TYPE_1__ Process ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  strncpy (scalar_t__,char const*,int) ; 
 scalar_t__ xStrdup (char const*) ; 

__attribute__((used)) static void setCommand(Process* process, const char* command, int len) {
   if (process->comm && process->commLen >= len) {
      strncpy(process->comm, command, len + 1);
   } else {
      free(process->comm);
      process->comm = xStrdup(command);
   }
   process->commLen = len;
}