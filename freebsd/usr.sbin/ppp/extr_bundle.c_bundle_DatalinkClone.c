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
struct datalink {int dummy; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 scalar_t__ bundle2datalink (struct bundle*,char const*) ; 
 int /*<<< orphan*/  bundle_DatalinkLinkin (struct bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datalink_Clone (struct datalink*,char const*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 

int
bundle_DatalinkClone(struct bundle *bundle, struct datalink *dl,
                     const char *name)
{
  if (bundle2datalink(bundle, name)) {
    log_Printf(LogWARN, "Clone: %s: name already exists\n", name);
    return 0;
  }

  bundle_DatalinkLinkin(bundle, datalink_Clone(dl, name));
  return 1;
}