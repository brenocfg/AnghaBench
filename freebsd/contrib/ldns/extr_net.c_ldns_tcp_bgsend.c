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
struct timeval {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int ldns_tcp_bgsend_from (int /*<<< orphan*/ *,struct sockaddr_storage const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval) ; 

int
ldns_tcp_bgsend(ldns_buffer *qbin,
		const struct sockaddr_storage *to, socklen_t tolen, 
		struct timeval timeout)
{
	return ldns_tcp_bgsend_from(qbin, to, tolen, NULL, 0, timeout);
}