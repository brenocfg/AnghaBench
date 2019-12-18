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
struct bundle {int unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0unlink (char*) ; 
 int PATH_MAX ; 
 char* _PATH_VARRUN ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static void
bundle_UnlockTun(struct bundle *bundle)
{
  char pidfile[PATH_MAX];

  snprintf(pidfile, sizeof pidfile, "%stun%d.pid", _PATH_VARRUN, bundle->unit);
  ID0unlink(pidfile);
}