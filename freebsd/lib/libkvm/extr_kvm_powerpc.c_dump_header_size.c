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
struct kerneldumpheader {int /*<<< orphan*/  architecture; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 char* KERNELDUMPMAGIC ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static size_t
dump_header_size(struct kerneldumpheader *dh)
{

	if (strcmp(dh->magic, KERNELDUMPMAGIC) != 0)
		return (0);
	if (strcmp(dh->architecture, "powerpc") != 0)
		return (0);
	/* That should do it... */
	return (sizeof(*dh));
}