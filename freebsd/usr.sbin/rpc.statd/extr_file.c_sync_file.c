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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ msync (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ status_info ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void sync_file(void)
{
  if (msync((void *)status_info, 0, 0) < 0)
  {
    syslog(LOG_ERR, "msync() failed: %s", strerror(errno));
  }
}