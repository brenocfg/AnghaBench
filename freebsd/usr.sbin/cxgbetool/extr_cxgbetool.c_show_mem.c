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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
show_mem(uint32_t *buf, uint32_t len)
{
	const char *s;
	int i, n = 8;

	while (len) {
		for (i = 0; len && i < n; i++, buf++, len -= 4) {
			s = i ? " " : "";
			printf("%s%08x", s, htonl(*buf));
		}
		printf("\n");
	}
}