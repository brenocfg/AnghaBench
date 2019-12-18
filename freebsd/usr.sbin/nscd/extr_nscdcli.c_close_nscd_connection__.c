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
struct nscd_connection_ {int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  sockfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_nscd_connection ; 
 int /*<<< orphan*/  free (struct nscd_connection_*) ; 

void
close_nscd_connection__(struct nscd_connection_ *connection)
{

	TRACE_IN(close_nscd_connection);
	assert(connection != NULL);

	close(connection->sockfd);
	close(connection->read_queue);
	close(connection->write_queue);
	free(connection);
	TRACE_OUT(close_nscd_connection);
}