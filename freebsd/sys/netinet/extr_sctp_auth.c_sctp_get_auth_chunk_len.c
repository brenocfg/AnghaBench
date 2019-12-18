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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sctp_auth_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_SIZE32 (int) ; 
 int sctp_get_hmac_digest_len (int /*<<< orphan*/ ) ; 

uint32_t
sctp_get_auth_chunk_len(uint16_t hmac_algo)
{
	int size;

	size = sizeof(struct sctp_auth_chunk) + sctp_get_hmac_digest_len(hmac_algo);
	return (SCTP_SIZE32(size));
}