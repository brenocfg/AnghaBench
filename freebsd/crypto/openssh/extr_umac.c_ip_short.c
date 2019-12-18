#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uhash_ctx_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {int* ip_trans; scalar_t__ ip_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  STORE_UINT32_BIG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip_aux (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int ip_reduce_p36 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip_short(uhash_ctx_t ahc, UINT8 *nh_res, u_char *res)
{
    UINT64 t;
    UINT64 *nhp = (UINT64 *)nh_res;

    t  = ip_aux(0,ahc->ip_keys, nhp[0]);
    STORE_UINT32_BIG((UINT32 *)res+0, ip_reduce_p36(t) ^ ahc->ip_trans[0]);
#if (UMAC_OUTPUT_LEN >= 8)
    t  = ip_aux(0,ahc->ip_keys+4, nhp[1]);
    STORE_UINT32_BIG((UINT32 *)res+1, ip_reduce_p36(t) ^ ahc->ip_trans[1]);
#endif
#if (UMAC_OUTPUT_LEN >= 12)
    t  = ip_aux(0,ahc->ip_keys+8, nhp[2]);
    STORE_UINT32_BIG((UINT32 *)res+2, ip_reduce_p36(t) ^ ahc->ip_trans[2]);
#endif
#if (UMAC_OUTPUT_LEN == 16)
    t  = ip_aux(0,ahc->ip_keys+12, nhp[3]);
    STORE_UINT32_BIG((UINT32 *)res+3, ip_reduce_p36(t) ^ ahc->ip_trans[3]);
#endif
}