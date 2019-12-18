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
struct creation_set {char* create_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 char* strdup (char const*) ; 

void
cset_set_format(struct creation_set *cset, const char *format)
{
	char *f;

	f = strdup(format);
	if (f == NULL)
		lafe_errc(1, 0, "No memory");
	free(cset->create_format);
	cset->create_format = f;
}