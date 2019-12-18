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
struct autr_ta {int /*<<< orphan*/  dname_len; int /*<<< orphan*/  rr_len; int /*<<< orphan*/  rr; } ;

/* Variables and functions */
 int DNSKEY_BIT_SEP ; 
 int dnskey_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdatalen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ta_is_dnskey_sep(struct autr_ta* ta)
{
	return (dnskey_flags(
		sldns_wirerr_get_type(ta->rr, ta->rr_len, ta->dname_len),
		sldns_wirerr_get_rdata(ta->rr, ta->rr_len, ta->dname_len),
		sldns_wirerr_get_rdatalen(ta->rr, ta->rr_len, ta->dname_len)
		) & DNSKEY_BIT_SEP);
}