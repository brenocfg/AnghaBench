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
struct listen_dnsport {scalar_t__ dnscrypt_udp_buff; scalar_t__ udp_buff; int /*<<< orphan*/  cps; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct listen_dnsport*) ; 
 int /*<<< orphan*/  listen_list_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_free (scalar_t__) ; 
 int /*<<< orphan*/  stream_wait_count_lock ; 
 scalar_t__ stream_wait_lock_inited ; 

void 
listen_delete(struct listen_dnsport* front)
{
	if(!front) 
		return;
	listen_list_delete(front->cps);
#ifdef USE_DNSCRYPT
	if(front->dnscrypt_udp_buff &&
		front->udp_buff != front->dnscrypt_udp_buff) {
		sldns_buffer_free(front->dnscrypt_udp_buff);
	}
#endif
	sldns_buffer_free(front->udp_buff);
	free(front);
	if(stream_wait_lock_inited) {
		stream_wait_lock_inited = 0;
		lock_basic_destroy(&stream_wait_count_lock);
	}
}