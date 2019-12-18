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

/* Variables and functions */
 int /*<<< orphan*/  add_history (char*) ; 
 int history_length ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 char* readline (char*) ; 

int
main(int argc, char *argv[])
{
	char *p;
	while ((p = readline("hi$")) != NULL) {
		add_history(p);
		printf("%d %s\n", history_length, p);
	}
	return 0;
}