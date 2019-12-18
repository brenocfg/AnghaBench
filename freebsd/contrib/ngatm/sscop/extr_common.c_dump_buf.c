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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void
dump_buf(const char *w, const u_char *buf, size_t len)
{
	u_int i;

	fprintf(stderr, "%s %zu: ", w, len);
	for(i = 0; i < len; i++) {
		if (i % 4 == 0 && i != 0)
			fprintf(stderr, " ");
		fprintf(stderr, "%02x", *buf++);
	}
	fprintf(stderr, "\n");
}