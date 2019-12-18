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
struct tuple_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dumpcis (struct tuple_list*) ; 
 int /*<<< orphan*/  freecis (struct tuple_list*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 struct tuple_list* readcis (int) ; 

__attribute__((used)) static void
scanfile(char *name)
{
	int     fd;
	struct tuple_list *tl;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return;
	tl = readcis(fd);
	if (tl) {
		printf("Configuration data for file %s\n",
		    name);
		dumpcis(tl);
		freecis(tl);
	}
	close(fd);
}