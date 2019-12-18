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
struct pathhead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* qstring (struct pathhead*) ; 

__attribute__((used)) static void
showpath(struct pathhead *pathq)
{
	char *s;

	if ((s = qstring(pathq)) == NULL) {
		errno = ENOMEM;
		err(1, "building path string");
	}
	printf("%s\n", s);
	free(s);
}