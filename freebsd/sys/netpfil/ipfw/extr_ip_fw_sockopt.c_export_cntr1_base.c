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
struct timeval {scalar_t__ tv_sec; } ;
struct ip_fw_bcounter {int size; scalar_t__ timestamp; void* bcnt; void* pcnt; } ;
struct ip_fw {scalar_t__ timestamp; int /*<<< orphan*/ * cntr; } ;

/* Variables and functions */
 void* counter_u64_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getboottime (struct timeval*) ; 

__attribute__((used)) static void
export_cntr1_base(struct ip_fw *krule, struct ip_fw_bcounter *cntr)
{
	struct timeval boottime;

	cntr->size = sizeof(*cntr);

	if (krule->cntr != NULL) {
		cntr->pcnt = counter_u64_fetch(krule->cntr);
		cntr->bcnt = counter_u64_fetch(krule->cntr + 1);
		cntr->timestamp = krule->timestamp;
	}
	if (cntr->timestamp > 0) {
		getboottime(&boottime);
		cntr->timestamp += boottime.tv_sec;
	}
}