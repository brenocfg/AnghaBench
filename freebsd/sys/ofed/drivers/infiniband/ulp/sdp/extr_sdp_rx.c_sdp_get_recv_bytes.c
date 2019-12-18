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
typedef  int /*<<< orphan*/  u32 ;
struct sdp_sock {int dummy; } ;

/* Variables and functions */
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDP_MAX_PACKET ; 

__attribute__((used)) static int
sdp_get_recv_bytes(struct sdp_sock *ssk, u32 new_size)
{

	return MIN(new_size, SDP_MAX_PACKET);
}