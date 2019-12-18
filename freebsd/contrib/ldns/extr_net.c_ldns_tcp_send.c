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
typedef  int /*<<< orphan*/  uint8_t ;
struct timeval {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_tcp_send_from (int /*<<< orphan*/ **,int /*<<< orphan*/ *,struct sockaddr_storage const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval,size_t*) ; 

ldns_status
ldns_tcp_send(uint8_t **result,  ldns_buffer *qbin,
		const struct sockaddr_storage *to, socklen_t tolen,
		struct timeval timeout, size_t *answer_size)
{
	return ldns_tcp_send_from(result, qbin,
			to, tolen, NULL, 0, timeout, answer_size);
}