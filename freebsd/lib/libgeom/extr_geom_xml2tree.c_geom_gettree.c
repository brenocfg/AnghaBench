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
struct gmesh {int dummy; } ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* geom_getxml () ; 
 int geom_xml2tree (struct gmesh*,char*) ; 

int
geom_gettree(struct gmesh *gmp)
{
	char *p;
	int error;

	p = geom_getxml();
	if (p == NULL)
		return (errno);
	error = geom_xml2tree(gmp, p);
	free(p);
	return (error);
}