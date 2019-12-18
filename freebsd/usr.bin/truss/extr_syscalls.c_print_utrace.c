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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ sysdecode_utrace (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static void
print_utrace(FILE *fp, void *utrace_addr, size_t len)
{
	unsigned char *utrace_buffer;

	fprintf(fp, "{ ");
	if (sysdecode_utrace(fp, utrace_addr, len)) {
		fprintf(fp, " }");
		return;
	}

	utrace_buffer = utrace_addr;
	fprintf(fp, "%zu:", len);
	while (len--)
		fprintf(fp, " %02x", *utrace_buffer++);
	fprintf(fp, " }");
}