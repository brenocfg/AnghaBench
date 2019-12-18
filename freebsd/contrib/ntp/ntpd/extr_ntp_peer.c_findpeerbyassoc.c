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
typedef  size_t u_int ;
struct peer {scalar_t__ associd; struct peer* aid_link; } ;
typedef  scalar_t__ associd_t ;

/* Variables and functions */
 scalar_t__ NTP_HASH_MASK ; 
 struct peer** assoc_hash ; 
 int /*<<< orphan*/  assocpeer_calls ; 

struct peer *
findpeerbyassoc(
	associd_t assoc
	)
{
	struct peer *p;
	u_int hash;

	assocpeer_calls++;
	hash = assoc & NTP_HASH_MASK;
	for (p = assoc_hash[hash]; p != NULL; p = p->aid_link)
		if (assoc == p->associd)
			break;
	return p;
}