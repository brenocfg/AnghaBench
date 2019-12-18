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
struct TYPE_3__ {int /*<<< orphan*/  machine; int /*<<< orphan*/  sysname; int /*<<< orphan*/  release; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_build ; 
 int /*<<< orphan*/  os_name ; 
 int /*<<< orphan*/  processor_arch ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  uname (TYPE_1__*) ; 
 TYPE_1__ uts_buf ; 

__attribute__((used)) static void
kvp_get_os_info(void)
{
	char *p;

	uname(&uts_buf);
	os_build = uts_buf.release;
	os_name = uts_buf.sysname;
	processor_arch = uts_buf.machine;

	/*
	 * Win7 host expects the build string to be of the form: x.y.z
	 * Strip additional information we may have.
	 */
	p = strchr(os_build, '-');
	if (p) {
		*p = '\0';
	}

	/*
	 * We don't have any other information about the FreeBSD os.
	 */
	return;
}