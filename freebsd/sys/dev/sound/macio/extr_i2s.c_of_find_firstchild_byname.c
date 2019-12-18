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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int OF_child (int) ; 
 int /*<<< orphan*/  OF_getprop (int,char*,char*,int) ; 
 int OF_peer (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static phandle_t
of_find_firstchild_byname(phandle_t node, const char *req_name)
{
	char 		name[32]; /* max name len per OF spec. */
	phandle_t 	n;

	for (n = OF_child(node); n != -1; n = OF_peer(n)) {
		bzero(name, sizeof(name));
		OF_getprop(n, "name", name, sizeof(name));

		if (strcmp(name, req_name) == 0)
			return (n);
	}

	return (-1);
}