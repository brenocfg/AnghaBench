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
typedef  int /*<<< orphan*/  t ;
struct if_ath_alq_tdma_timer_set {int /*<<< orphan*/  sc_tdmaswbaprep; int /*<<< orphan*/  sc_tdmadbaprep; int /*<<< orphan*/  bt_flags; int /*<<< orphan*/  bt_nextatim; int /*<<< orphan*/  bt_nextswba; int /*<<< orphan*/  bt_nextdba; int /*<<< orphan*/  bt_nexttbtt; int /*<<< orphan*/  bt_intval; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct if_ath_alq_tdma_timer_set*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned long long,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ath_tdma_timer_set(struct if_ath_alq_payload *a)
{
	struct if_ath_alq_tdma_timer_set t;

	memcpy(&t, &a->payload, sizeof(t));
	printf("[%u] [%llu] TIMERSET: bt_intval=%d nexttbtt=%d nextdba=%d nextswba=%d nextatim=%d flags=0x%x tdmadbaprep=%d tdmaswbaprep=%d\n",
	    (unsigned int) be32toh(a->hdr.tstamp),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    be32toh(t.bt_intval),
	    be32toh(t.bt_nexttbtt),
	    be32toh(t.bt_nextdba),
	    be32toh(t.bt_nextswba),
	    be32toh(t.bt_nextatim),
	    be32toh(t.bt_flags),
	    be32toh(t.sc_tdmadbaprep),
	    be32toh(t.sc_tdmaswbaprep));
}