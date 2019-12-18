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
struct modversion_info {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void dedotify_versions(struct modversion_info *vers,
			      unsigned long size)
{
	struct modversion_info *end;

	for (end = (void *)vers + size; vers < end; vers++)
		if (vers->name[0] == '.') {
			memmove(vers->name, vers->name+1, strlen(vers->name));
		}
}