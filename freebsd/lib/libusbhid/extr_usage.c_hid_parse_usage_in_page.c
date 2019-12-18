#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pagesize; int usage; TYPE_1__* page_contents; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int usage; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int npages ; 
 TYPE_2__* pages ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 

int
hid_parse_usage_in_page(const char *name)
{
	const char *sep;
	int k, j;
	unsigned int l;

	sep = strchr(name, ':');
	if (sep == NULL)
		return -1;
	l = sep - name;
	for (k = 0; k < npages; k++)
		if (strncmp(pages[k].name, name, l) == 0)
			goto found;
	return -1;
 found:
	sep++;
	for (j = 0; j < pages[k].pagesize; j++)
		if (strcmp(pages[k].page_contents[j].name, sep) == 0)
			return (pages[k].usage << 16) | pages[k].page_contents[j].usage;
	return (-1);
}