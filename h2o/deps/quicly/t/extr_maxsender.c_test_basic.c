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
typedef  int /*<<< orphan*/  quicly_maxsender_t ;
typedef  int /*<<< orphan*/  quicly_maxsender_sent_t ;

/* Variables and functions */
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  quicly_maxsender_acked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  quicly_maxsender_lost (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_maxsender_record (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int quicly_maxsender_should_send_max (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void test_basic(void)
{
    quicly_maxsender_t m;
    quicly_maxsender_sent_t ackargs;

    quicly_maxsender_init(&m, 100);

    /* basic checks */
    ok(!quicly_maxsender_should_send_max(&m, 0, 100, 512));
    ok(quicly_maxsender_should_send_max(&m, 0, 100, 1024));
    ok(!quicly_maxsender_should_send_max(&m, 99, 100, 0));
    ok(quicly_maxsender_should_send_max(&m, 100, 100, 0));

    /* scenario */
    ok(!quicly_maxsender_should_send_max(&m, 24, 100, 768));
    ok(quicly_maxsender_should_send_max(&m, 25, 100, 768));
    quicly_maxsender_record(&m, 125, &ackargs);
    ok(!quicly_maxsender_should_send_max(&m, 49, 100, 768));
    ok(quicly_maxsender_should_send_max(&m, 50, 100, 768));
    quicly_maxsender_acked(&m, &ackargs);
    ok(!quicly_maxsender_should_send_max(&m, 49, 100, 768));
    ok(quicly_maxsender_should_send_max(&m, 50, 100, 768));
    quicly_maxsender_record(&m, 150, &ackargs);
    ok(!quicly_maxsender_should_send_max(&m, 74, 100, 768));
    quicly_maxsender_lost(&m, &ackargs);
    ok(quicly_maxsender_should_send_max(&m, 74, 100, 768));
}