#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct rpl_dio_genoption {int dummy; } ;
struct nd_rpl_dio {int /*<<< orphan*/  rpl_mopprf; int /*<<< orphan*/  rpl_dagrank; int /*<<< orphan*/  rpl_instanceid; int /*<<< orphan*/  rpl_dtsn; int /*<<< orphan*/  rpl_dagid; } ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct nd_rpl_dio const) ; 
 scalar_t__ RPL_DIO_GROUNDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPL_DIO_MOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPL_DIO_PRF (int /*<<< orphan*/ ) ; 
 char* ip6addr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpl_dio_printopt (TYPE_1__*,struct rpl_dio_genoption const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpl_mop_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rpl_dio_print(netdissect_options *ndo,
              const u_char *bp, u_int length)
{
        const struct nd_rpl_dio *dio = (const struct nd_rpl_dio *)bp;
        const char *dagid_str;

        ND_TCHECK(*dio);
        dagid_str = ip6addr_string (ndo, dio->rpl_dagid);

        ND_PRINT((ndo, " [dagid:%s,seq:%u,instance:%u,rank:%u,%smop:%s,prf:%u]",
                  dagid_str,
                  dio->rpl_dtsn,
                  dio->rpl_instanceid,
                  EXTRACT_16BITS(&dio->rpl_dagrank),
                  RPL_DIO_GROUNDED(dio->rpl_mopprf) ? "grounded,":"",
                  tok2str(rpl_mop_values, "mop%u", RPL_DIO_MOP(dio->rpl_mopprf)),
                  RPL_DIO_PRF(dio->rpl_mopprf)));

        if(ndo->ndo_vflag > 1) {
                const struct rpl_dio_genoption *opt = (const struct rpl_dio_genoption *)&dio[1];
                rpl_dio_printopt(ndo, opt, length);
        }
	return;
trunc:
	ND_PRINT((ndo," [|truncated]"));
	return;
}