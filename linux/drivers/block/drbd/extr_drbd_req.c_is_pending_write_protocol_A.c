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
struct drbd_request {int rq_state; } ;

/* Variables and functions */
 int RQ_EXP_RECEIVE_ACK ; 
 int RQ_EXP_WRITE_ACK ; 
 int RQ_NET_PENDING ; 
 int RQ_WRITE ; 

__attribute__((used)) static inline bool is_pending_write_protocol_A(struct drbd_request *req)
{
	return (req->rq_state &
		   (RQ_WRITE|RQ_NET_PENDING|RQ_EXP_WRITE_ACK|RQ_EXP_RECEIVE_ACK))
		== (RQ_WRITE|RQ_NET_PENDING);
}