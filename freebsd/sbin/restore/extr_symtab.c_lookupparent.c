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
struct entry {scalar_t__ e_type; } ;

/* Variables and functions */
 scalar_t__ NODE ; 
 struct entry* lookupname (char*) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static struct entry *
lookupparent(char *name)
{
	struct entry *ep;
	char *tailindex;

	tailindex = strrchr(name, '/');
	if (tailindex == NULL)
		return (NULL);
	*tailindex = '\0';
	ep = lookupname(name);
	*tailindex = '/';
	if (ep == NULL)
		return (NULL);
	if (ep->e_type != NODE)
		panic("%s is not a directory\n", name);
	return (ep);
}