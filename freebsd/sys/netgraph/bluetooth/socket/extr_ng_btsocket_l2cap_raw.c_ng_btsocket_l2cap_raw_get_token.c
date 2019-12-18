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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ng_btsocket_l2cap_raw_token ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_raw_token_mtx ; 

__attribute__((used)) static void
ng_btsocket_l2cap_raw_get_token(u_int32_t *token)
{
	mtx_lock(&ng_btsocket_l2cap_raw_token_mtx);
  
	if (++ ng_btsocket_l2cap_raw_token == 0)
		ng_btsocket_l2cap_raw_token = 1;
 
	*token = ng_btsocket_l2cap_raw_token;
 
	mtx_unlock(&ng_btsocket_l2cap_raw_token_mtx);
}