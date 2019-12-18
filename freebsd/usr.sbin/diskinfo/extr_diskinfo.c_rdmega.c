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
 int MEGATX ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdmega(int fd)
{
	int error;

	error = read(fd, buf, MEGATX);
	if (error == -1)
		err(1, "read");
	if (error != MEGATX)
		errx(1, "disk too small for test.");
}