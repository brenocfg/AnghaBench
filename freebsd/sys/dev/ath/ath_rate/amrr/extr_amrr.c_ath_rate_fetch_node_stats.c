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
struct ath_softc {int dummy; } ;
struct ath_rateioctl {int dummy; } ;
struct ath_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
ath_rate_fetch_node_stats(struct ath_softc *sc, struct ath_node *an,
    struct ath_rateioctl *re)
{

	return (EINVAL);
}