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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_int(FILE *fp, uint64_t v, size_t nbytes)
{
    size_t i;
    for (i = 0; i != nbytes; ++i)
        fputc((uint8_t)(v >> ((nbytes - i - 1) * 8)), fp);
}