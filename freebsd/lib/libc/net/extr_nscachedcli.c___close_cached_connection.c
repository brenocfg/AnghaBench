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
struct cached_connection_ {int /*<<< orphan*/  write_queue; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  sockfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  _close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cached_connection_*) ; 

void
__close_cached_connection(struct cached_connection_ *connection)
{
	assert(connection != NULL);

	_close(connection->sockfd);
	_close(connection->read_queue);
	_close(connection->write_queue);
	free(connection);
}