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
typedef  scalar_t__ uint8_t ;
struct ecore_rss_config_obj {int /*<<< orphan*/  ind_table; scalar_t__ udp_rss_v6; scalar_t__ udp_rss_v4; } ;
struct ecore_config_rss_params {int /*<<< orphan*/  rss_flags; int /*<<< orphan*/ * rss_key; int /*<<< orphan*/  ind_table; int /*<<< orphan*/  rss_result_mask; int /*<<< orphan*/  ramrod_flags; struct ecore_rss_config_obj* rss_obj; int /*<<< orphan*/ * member_0; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_RSS_IPV4 ; 
 int /*<<< orphan*/  ECORE_RSS_IPV4_TCP ; 
 int /*<<< orphan*/  ECORE_RSS_IPV4_UDP ; 
 int /*<<< orphan*/  ECORE_RSS_IPV6 ; 
 int /*<<< orphan*/  ECORE_RSS_IPV6_TCP ; 
 int /*<<< orphan*/  ECORE_RSS_IPV6_UDP ; 
 int /*<<< orphan*/  ECORE_RSS_MODE_REGULAR ; 
 int /*<<< orphan*/  ECORE_RSS_SET_SRCH ; 
 int /*<<< orphan*/  MULTI_MASK ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_config_rss (struct bxe_softc*,struct ecore_config_rss_params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bxe_config_rss_pf(struct bxe_softc            *sc,
                  struct ecore_rss_config_obj *rss_obj,
                  uint8_t                     config_hash)
{
    struct ecore_config_rss_params params = { NULL };
    int i;

    /*
     * Although RSS is meaningless when there is a single HW queue we
     * still need it enabled in order to have HW Rx hash generated.
     */

    params.rss_obj = rss_obj;

    bxe_set_bit(RAMROD_COMP_WAIT, &params.ramrod_flags);

    bxe_set_bit(ECORE_RSS_MODE_REGULAR, &params.rss_flags);

    /* RSS configuration */
    bxe_set_bit(ECORE_RSS_IPV4, &params.rss_flags);
    bxe_set_bit(ECORE_RSS_IPV4_TCP, &params.rss_flags);
    bxe_set_bit(ECORE_RSS_IPV6, &params.rss_flags);
    bxe_set_bit(ECORE_RSS_IPV6_TCP, &params.rss_flags);
    if (rss_obj->udp_rss_v4) {
        bxe_set_bit(ECORE_RSS_IPV4_UDP, &params.rss_flags);
    }
    if (rss_obj->udp_rss_v6) {
        bxe_set_bit(ECORE_RSS_IPV6_UDP, &params.rss_flags);
    }

    /* Hash bits */
    params.rss_result_mask = MULTI_MASK;

    memcpy(params.ind_table, rss_obj->ind_table, sizeof(params.ind_table));

    if (config_hash) {
        /* RSS keys */
        for (i = 0; i < sizeof(params.rss_key) / 4; i++) {
            params.rss_key[i] = arc4random();
        }

        bxe_set_bit(ECORE_RSS_SET_SRCH, &params.rss_flags);
    }

    return (ecore_config_rss(sc, &params));
}