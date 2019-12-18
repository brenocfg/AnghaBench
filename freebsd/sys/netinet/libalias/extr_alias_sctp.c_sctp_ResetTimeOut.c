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
struct sctp_nat_assoc {int exp; } ;
struct libalias {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_AddTimeOut (struct libalias*,struct sctp_nat_assoc*) ; 
 int /*<<< orphan*/  sctp_RmTimeOut (struct libalias*,struct sctp_nat_assoc*) ; 

__attribute__((used)) static void
sctp_ResetTimeOut(struct libalias *la, struct sctp_nat_assoc *assoc, int newexp)
{
	if (newexp < assoc->exp) {
		sctp_RmTimeOut(la, assoc);
		assoc->exp = newexp;
		sctp_AddTimeOut(la, assoc);
	} else {
		assoc->exp = newexp;
	}
}