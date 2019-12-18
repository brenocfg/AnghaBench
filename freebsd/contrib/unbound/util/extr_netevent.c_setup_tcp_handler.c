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
struct comm_point {scalar_t__ type; int fd; int tcp_is_reading; int tcp_timeout_msec; scalar_t__ tcp_byte_count; int /*<<< orphan*/  dnscrypt_buffer; scalar_t__ dnscrypt; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int TCP_QUERY_TIMEOUT_MINIMUM ; 
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int) ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setup_tcp_handler(struct comm_point* c, int fd, int cur, int max) 
{
	int handler_usage;
	log_assert(c->type == comm_tcp);
	log_assert(c->fd == -1);
	sldns_buffer_clear(c->buffer);
#ifdef USE_DNSCRYPT
	if (c->dnscrypt)
		sldns_buffer_clear(c->dnscrypt_buffer);
#endif
	c->tcp_is_reading = 1;
	c->tcp_byte_count = 0;
	/* if more than half the tcp handlers are in use, use a shorter
	 * timeout for this TCP connection, we need to make space for
	 * other connections to be able to get attention */
	/* If > 50% TCP handler structures in use, set timeout to 1/100th
	 * 	configured value.
	 * If > 65%TCP handler structures in use, set to 1/500th configured
	 * 	value.
	 * If > 80% TCP handler structures in use, set to 0.
	 *
	 * If the timeout to use falls below 200 milliseconds, an actual
	 * timeout of 200ms is used.
	 */
	handler_usage = (cur * 100) / max;
	if(handler_usage > 50 && handler_usage <= 65)
		c->tcp_timeout_msec /= 100;
	else if (handler_usage > 65 && handler_usage <= 80)
		c->tcp_timeout_msec /= 500;
	else if (handler_usage > 80)
		c->tcp_timeout_msec = 0;
	comm_point_start_listening(c, fd,
		c->tcp_timeout_msec < TCP_QUERY_TIMEOUT_MINIMUM
			? TCP_QUERY_TIMEOUT_MINIMUM
			: c->tcp_timeout_msec);
}