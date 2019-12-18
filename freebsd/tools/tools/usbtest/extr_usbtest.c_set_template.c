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
typedef  int /*<<< orphan*/  template ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void
set_template(int template)
{
	int error;

	error = sysctlbyname("hw.usb.template", NULL, NULL,
	    &template, sizeof(template));

	if (error != 0) {
		printf("WARNING: Could not set USB template "
		    "to %d (error=%d)\n", template, errno);
	}
}