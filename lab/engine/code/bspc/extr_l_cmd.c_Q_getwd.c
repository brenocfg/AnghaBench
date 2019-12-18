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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * getcwd (char*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void Q_getwd (char *out, size_t size)
{
   assert(size >= 2);
   if (NULL == getcwd(out, size - 2)) {
      perror("getcwd");
      exit(1);
   }
#if defined(WIN32) || defined(_WIN32)
   strcat(out, "\\");
#else
   strcat(out, "/");
#endif
}