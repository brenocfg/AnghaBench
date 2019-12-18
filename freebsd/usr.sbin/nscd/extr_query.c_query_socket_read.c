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
struct query_state {int socket_failed; int /*<<< orphan*/  sockfd; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*,void*,size_t)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*,void*,size_t)) ; 
 int read (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t
query_socket_read(struct query_state *qstate, void *buf, size_t nbytes)
{
	ssize_t	result;

	TRACE_IN(query_socket_read);
	if (qstate->socket_failed != 0) {
		TRACE_OUT(query_socket_read);
		return (-1);
	}

	result = read(qstate->sockfd, buf, nbytes);
	if (result < 0 || (size_t)result < nbytes)
		qstate->socket_failed = 1;

	TRACE_OUT(query_socket_read);
	return (result);
}