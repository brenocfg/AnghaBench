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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  print_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  tpl32 (int*) ; 

__attribute__((used)) static void
dump_bar(u_char *p, int len)
{
	if (len < 6) {
		printf("\tWrong length for BAR tuple\n");
		return;
	}
	printf("\tBAR %d: size = ", *p & 7);
	print_size(tpl32(p + 2));
	printf(", %s%s%s%s\n",
	       (*p & 0x10) ? "I/O" : "Memory",
	       (*p & 0x20) ? ", Prefetch" : "",
	       (*p & 0x40) ? ", Cacheable" : "",
	       (*p & 0x80) ? ", <1Mb" : "");
}