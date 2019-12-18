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
struct dosDirEntry {struct dosDirEntry* next; } ;

/* Variables and functions */
 struct dosDirEntry* freede ; 
 struct dosDirEntry* malloc (int) ; 

__attribute__((used)) static struct dosDirEntry *
newDosDirEntry(void)
{
	struct dosDirEntry *de;

	if (!(de = freede)) {
		if (!(de = malloc(sizeof *de)))
			return 0;
	} else
		freede = de->next;
	return de;
}