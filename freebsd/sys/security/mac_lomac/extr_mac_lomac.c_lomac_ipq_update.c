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
struct mbuf {int dummy; } ;
struct label {int dummy; } ;
struct ipq {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
lomac_ipq_update(struct mbuf *m, struct label *mlabel, struct ipq *q,
    struct label *qlabel)
{

	/* NOOP: we only accept matching labels, so no need to update */
}