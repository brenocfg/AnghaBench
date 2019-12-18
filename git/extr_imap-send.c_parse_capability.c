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
struct imap {int caps; int rcaps; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cap_list ; 
 char* next_arg (char**) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void parse_capability(struct imap *imap, char *cmd)
{
	char *arg;
	unsigned i;

	imap->caps = 0x80000000;
	while ((arg = next_arg(&cmd)))
		for (i = 0; i < ARRAY_SIZE(cap_list); i++)
			if (!strcmp(cap_list[i], arg))
				imap->caps |= 1 << i;
	imap->rcaps = imap->caps;
}