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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshmac {size_t mac_len; } ;
typedef  int /*<<< orphan*/  ourmac ;

/* Variables and functions */
 int SSH_DIGEST_MAX_LENGTH ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_MAC_INVALID ; 
 int mac_compute (struct sshmac*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 scalar_t__ timingsafe_bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

int
mac_check(struct sshmac *mac, u_int32_t seqno,
    const u_char *data, size_t dlen,
    const u_char *theirmac, size_t mlen)
{
	u_char ourmac[SSH_DIGEST_MAX_LENGTH];
	int r;

	if (mac->mac_len > mlen)
		return SSH_ERR_INVALID_ARGUMENT;
	if ((r = mac_compute(mac, seqno, data, dlen,
	    ourmac, sizeof(ourmac))) != 0)
		return r;
	if (timingsafe_bcmp(ourmac, theirmac, mac->mac_len) != 0)
		return SSH_ERR_MAC_INVALID;
	return 0;
}