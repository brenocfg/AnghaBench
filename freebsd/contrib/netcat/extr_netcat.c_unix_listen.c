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
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ listen (int,int) ; 
 int unix_bind (char*) ; 

int
unix_listen(char *path)
{
	int s;
	if ((s = unix_bind(path)) < 0)
		return (-1);

	if (listen(s, 5) < 0) {
		close(s);
		return (-1);
	}
	return (s);
}