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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
receive_and_exit(int s)
{
	ssize_t ssize;
	char ch;

	ssize = recv(s, &ch, sizeof(ch), 0);
	if (ssize < 0)
		err(-1, "receive_and_exit: recv");
	exit(0);
}