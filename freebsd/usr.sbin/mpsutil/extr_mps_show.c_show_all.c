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
 int /*<<< orphan*/  printf (char*) ; 
 int show_adapter (int,char**) ; 
 int show_devices (int,char**) ; 
 int show_enclosures (int,char**) ; 
 int show_expanders (int,char**) ; 

__attribute__((used)) static int
show_all(int ac, char **av)
{
	int error;

	printf("Adapter:\n");
	error = show_adapter(ac, av);
	printf("Devices:\n");
	error = show_devices(ac, av);
	printf("Enclosures:\n");
	error = show_enclosures(ac, av);
	printf("Expanders:\n");
	error = show_expanders(ac, av);
	return (error);
}