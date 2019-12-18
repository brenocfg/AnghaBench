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
typedef  int /*<<< orphan*/  u64 ;
struct class_attribute {int dummy; } ;
struct class {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int kstrtou64 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_mobility_fixup () ; 
 int rtas_ibm_suspend_me (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 
 int /*<<< orphan*/  start_topology_update () ; 
 int /*<<< orphan*/  stop_topology_update () ; 

__attribute__((used)) static ssize_t migration_store(struct class *class,
			       struct class_attribute *attr, const char *buf,
			       size_t count)
{
	u64 streamid;
	int rc;

	rc = kstrtou64(buf, 0, &streamid);
	if (rc)
		return rc;

	stop_topology_update();

	do {
		rc = rtas_ibm_suspend_me(streamid);
		if (rc == -EAGAIN)
			ssleep(1);
	} while (rc == -EAGAIN);

	if (rc)
		return rc;

	post_mobility_fixup();

	start_topology_update();

	return count;
}