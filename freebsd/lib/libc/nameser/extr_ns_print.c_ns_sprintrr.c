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
typedef  int /*<<< orphan*/  ns_rr ;
typedef  int /*<<< orphan*/  ns_msg ;

/* Variables and functions */
 int /*<<< orphan*/  ns_msg_base (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_msg_size (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_class (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_name (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_rdata (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_rdlen (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_ttl (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ns_rr_type (int /*<<< orphan*/  const) ; 
 int ns_sprintrrf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char*,size_t) ; 

int
ns_sprintrr(const ns_msg *handle, const ns_rr *rr,
	    const char *name_ctx, const char *origin,
	    char *buf, size_t buflen)
{
	int n;

	n = ns_sprintrrf(ns_msg_base(*handle), ns_msg_size(*handle),
			 ns_rr_name(*rr), ns_rr_class(*rr), ns_rr_type(*rr),
			 ns_rr_ttl(*rr), ns_rr_rdata(*rr), ns_rr_rdlen(*rr),
			 name_ctx, origin, buf, buflen);
	return (n);
}