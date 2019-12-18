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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_vector(const char * msg, uint32_t * v, size_t len)
{
    size_t i;

    printf("%s: (%d) ", msg, (int)len);
    for (i=0; i < len; i++) {
	printf("%s%x", (i > 0? " ":""), v[i]);
    }
    printf("\n");
}