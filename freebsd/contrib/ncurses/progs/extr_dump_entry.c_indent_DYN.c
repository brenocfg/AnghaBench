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
typedef  int /*<<< orphan*/  DYNBUF ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy_DYN (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static void
indent_DYN(DYNBUF * buffer, int level)
{
    int n;

    for (n = 0; n < level; n++)
	strncpy_DYN(buffer, "\t", (size_t) 1);
}