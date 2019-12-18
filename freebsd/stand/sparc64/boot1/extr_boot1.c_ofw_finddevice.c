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
typedef  int ofwh_t ;
typedef  int ofwcell_t ;

/* Variables and functions */
 scalar_t__ ofw (int*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ stub1 (int*) ; 

__attribute__((used)) static ofwh_t
ofw_finddevice(const char *name)
{
	ofwcell_t args[] = {
		(ofwcell_t)"finddevice",
		1,
		1,
		(ofwcell_t)name,
		0
	};

	if ((*ofw)(args)) {
		printf("ofw_finddevice: name=\"%s\"\n", name);
		return (1);
	}
	return (args[4]);
}