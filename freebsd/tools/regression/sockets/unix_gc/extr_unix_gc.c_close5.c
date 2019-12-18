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
 int /*<<< orphan*/  close2 (int,int) ; 
 int /*<<< orphan*/  close3 (int,int,int) ; 

__attribute__((used)) static void
close5(int fd1, int fd2, int fd3, int fd4, int fd5)
{

	close3(fd1, fd2, fd3);
	close2(fd4, fd5);
}