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
typedef  int /*<<< orphan*/  stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_stat (int /*<<< orphan*/ *,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
show_stats(stat_t *sp, char *what)
{
	const char *s = "";
	char *w;

	for (w = strtok(what, ","); w != NULL; w = strtok(NULL, ",")) {
		printf("%s", s);
		show_stat(sp, w);
		s = ",";
	}
	printf("\n");
}