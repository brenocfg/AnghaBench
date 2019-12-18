#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int AHSLength; size_t DSLength; } ;
struct TYPE_10__ {TYPE_6__ bhs; } ;
struct TYPE_13__ {int ahs_len; size_t ds_len; TYPE_1__ ipdu; } ;
struct TYPE_12__ {size_t len; TYPE_4__ pdu; } ;
typedef  TYPE_3__ pduq_t ;
typedef  TYPE_4__ pdu_t ;
struct TYPE_11__ {size_t maxBurstLength; } ;
struct TYPE_14__ {TYPE_2__ opt; int /*<<< orphan*/  sid; int /*<<< orphan*/  dataDigest; int /*<<< orphan*/  hdrDigest; } ;
typedef  TYPE_5__ isc_session_t ;
typedef  TYPE_6__ bhs_t ;

/* Variables and functions */
 int E2BIG ; 
 scalar_t__ ISOK2DIG (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  xdebug (char*,int /*<<< orphan*/ ,size_t,size_t) ; 

int
i_prepPDU(isc_session_t *sp, pduq_t *pq)
{
     size_t	len, n;
     pdu_t	*pp = &pq->pdu;
     bhs_t	*bhp = &pp->ipdu.bhs;

     len = sizeof(bhs_t);
     if(pp->ahs_len) {
	  len += pp->ahs_len;
	  bhp->AHSLength =  pp->ahs_len / 4;
     }
     if(ISOK2DIG(sp->hdrDigest, pp))
	  len += 4;
     if(pp->ds_len) {
	  n = pp->ds_len;
	  len += n;
#if BYTE_ORDER == LITTLE_ENDIAN
	  bhp->DSLength = ((n & 0x00ff0000) >> 16)
	       | (n & 0x0000ff00)
	       | ((n & 0x000000ff) << 16);
#else
	  bhp->DSLength = n;
#endif
	  if(len & 03) {
	       n = 4 - (len & 03);
	       len += n;
	  }
	  if(ISOK2DIG(sp->dataDigest, pp))
	       len += 4;
     }

     pq->len = len;
     len -= sizeof(bhs_t);
     if(sp->opt.maxBurstLength && (len > sp->opt.maxBurstLength)) {
	  xdebug("%d] pdu len=%zd > %d",
		 sp->sid, len, sp->opt.maxBurstLength);
	  // XXX: when this happens it used to hang ...
	  return E2BIG;
     }
     return 0;
}