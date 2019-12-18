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
typedef  scalar_t__ uint32_t ;
typedef  int u_int32_t ;
struct svc_rpc_gss_client {scalar_t__ cl_seqlast; int* cl_seqmask; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVC_RPC_GSS_SEQWINDOW ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bool_t
svc_rpc_gss_check_replay(struct svc_rpc_gss_client *client, uint32_t seq)
{
	u_int32_t offset;
	int word, bit;

	if (seq <= client->cl_seqlast) {
		/*
		 * The request sequence number is less than
		 * the largest we have seen so far. If it is
		 * outside the window or if we have seen a
		 * request with this sequence before, silently
		 * discard it.
		 */
		offset = client->cl_seqlast - seq;
		if (offset >= SVC_RPC_GSS_SEQWINDOW)
			return (FALSE);
		word = offset / 32;
		bit = offset % 32;
		if (client->cl_seqmask[word] & (1 << bit))
			return (FALSE);
	}

	return (TRUE);
}