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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_SD_PROTO_NOT_AVAILABLE ; 
 int /*<<< orphan*/  wpas_sd_add_empty (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_sd_add_proto_not_avail(struct wpabuf *resp, u8 srv_proto,
					u8 srv_trans_id)
{
	wpas_sd_add_empty(resp, srv_proto, srv_trans_id,
			  P2P_SD_PROTO_NOT_AVAILABLE);
}