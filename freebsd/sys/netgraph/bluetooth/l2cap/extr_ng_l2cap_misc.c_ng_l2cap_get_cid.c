#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_int16_t ;
typedef  TYPE_1__* ng_l2cap_p ;
struct TYPE_4__ {int lecid; int cid; } ;

/* Variables and functions */
 int NG_L2CAP_FIRST_CID ; 
 int NG_L2CAP_L2CA_IDTYPE_BREDR ; 
 int NG_L2CAP_L2CA_IDTYPE_LE ; 
 int NG_L2CAP_LAST_CID ; 
 int NG_L2CAP_LELAST_CID ; 
 int NG_L2CAP_NULL_CID ; 
 int /*<<< orphan*/ * ng_l2cap_chan_by_scid (TYPE_1__*,int,int) ; 

__attribute__((used)) static u_int16_t
ng_l2cap_get_cid(ng_l2cap_p l2cap,int isle)
{
	u_int16_t	cid ;
	u_int16_t 	endcid;
	uint16_t	 mask;
	int idtype;
	if(isle){
		endcid = l2cap->lecid;
		/*Assume Last CID is 2^n-1 */
		mask = NG_L2CAP_LELAST_CID;
		idtype = NG_L2CAP_L2CA_IDTYPE_LE;
	}else{
		endcid = l2cap->cid;
		/*Assume Last CID is 2^n-1 */		
		mask = NG_L2CAP_LAST_CID;
		idtype = NG_L2CAP_L2CA_IDTYPE_BREDR;
	}
	cid = (endcid+1) & mask;
	     
	if (cid < NG_L2CAP_FIRST_CID)
		cid = NG_L2CAP_FIRST_CID;

	while (cid != endcid) {
		if (ng_l2cap_chan_by_scid(l2cap, cid, idtype) == NULL) {
			if(!isle){
				l2cap->cid = cid;
			}else{
				l2cap->lecid = cid;
			}
			return (cid);
		}

		cid ++;
		cid &= mask;
		if (cid < NG_L2CAP_FIRST_CID)
			cid = NG_L2CAP_FIRST_CID;
	}
		
	return (NG_L2CAP_NULL_CID);
}