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
typedef  int u32 ;
struct drbd_connection {int agreed_pro_version; int agreed_features; } ;
struct bio {int bi_opf; } ;

/* Variables and functions */
 int DP_DISCARD ; 
 int DP_FLUSH ; 
 int DP_FUA ; 
 int DP_RW_SYNC ; 
 int DP_WSAME ; 
 int DP_ZEROES ; 
 int DRBD_FF_WZEROES ; 
 int REQ_FUA ; 
 int REQ_NOUNMAP ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_WRITE_SAME ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 scalar_t__ bio_op (struct bio*) ; 

__attribute__((used)) static u32 bio_flags_to_wire(struct drbd_connection *connection,
			     struct bio *bio)
{
	if (connection->agreed_pro_version >= 95)
		return  (bio->bi_opf & REQ_SYNC ? DP_RW_SYNC : 0) |
			(bio->bi_opf & REQ_FUA ? DP_FUA : 0) |
			(bio->bi_opf & REQ_PREFLUSH ? DP_FLUSH : 0) |
			(bio_op(bio) == REQ_OP_WRITE_SAME ? DP_WSAME : 0) |
			(bio_op(bio) == REQ_OP_DISCARD ? DP_DISCARD : 0) |
			(bio_op(bio) == REQ_OP_WRITE_ZEROES ?
			  ((connection->agreed_features & DRBD_FF_WZEROES) ?
			   (DP_ZEROES |(!(bio->bi_opf & REQ_NOUNMAP) ? DP_DISCARD : 0))
			   : DP_DISCARD)
			: 0);
	else
		return bio->bi_opf & REQ_SYNC ? DP_RW_SYNC : 0;
}