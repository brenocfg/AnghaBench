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
 char* cap2str (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_caps(int caps)
{
	int i, need_coma;

	need_coma = 0;
	printf("<");
	for (i = 0; i < 32; i++) {
		if (caps & (1 << i)) {
			if (need_coma)
				printf(",");
			printf("%s", cap2str(1 << i));
			need_coma = 1;
		}
	}
	printf(">");
}