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
 int /*<<< orphan*/  datagram_test () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  stream_test () ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

int
main(void)
{
	
	if (mkstemp(socket_path) == -1)
		err(1, "mkstemp failed");
	(void)unlink(socket_path);
	datagram_test();
	if (0)
		stream_test();
	return (0);
}