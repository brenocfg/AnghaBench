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
struct sysctl_req {int dummy; } ;

/* Variables and functions */
 int SYSCTL_OUT (struct sysctl_req*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
sysctl_kern_function_list_iterate(const char *name, void *opaque)
{
	struct sysctl_req *req;

	req = opaque;
	return (SYSCTL_OUT(req, name, strlen(name) + 1));
}