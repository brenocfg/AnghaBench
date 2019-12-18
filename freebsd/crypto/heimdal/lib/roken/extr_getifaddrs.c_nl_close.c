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
 int /*<<< orphan*/  __close (int) ; 
 int /*<<< orphan*/  __set_errno (int) ; 
 int errno ; 

__attribute__((used)) static void
nl_close(int sd)
{
  int saved_errno = errno;
  if (sd >= 0) __close(sd);
  __set_errno(saved_errno);
}