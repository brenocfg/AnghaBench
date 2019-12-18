#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int tso_segsz; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int ETH_TX_PARSE_BD_E2_LSO_MSS ; 
 int ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT ; 

__attribute__((used)) static void
bxe_set_pbd_lso_e2(struct mbuf *m,
                   uint32_t    *parsing_data)
{
    *parsing_data |= ((m->m_pkthdr.tso_segsz <<
                       ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT) &
                      ETH_TX_PARSE_BD_E2_LSO_MSS);

    /* XXX test for IPv6 with extension header... */
}