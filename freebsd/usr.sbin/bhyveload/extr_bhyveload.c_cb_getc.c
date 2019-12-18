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
 int /*<<< orphan*/  consin_fd ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
cb_getc(void *arg)
{
	char c;

	if (read(consin_fd, &c, 1) == 1)
		return (c);
	return (-1);
}