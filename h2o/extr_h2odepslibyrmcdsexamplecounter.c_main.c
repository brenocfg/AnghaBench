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
typedef  int /*<<< orphan*/  yrmcds_cnt_response ;
typedef  int /*<<< orphan*/  yrmcds_cnt ;

/* Variables and functions */
 int /*<<< orphan*/  check_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_cnt_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_cnt_connect (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  yrmcds_cnt_noop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_cnt_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(void) {
    yrmcds_cnt c;
    yrmcds_cnt_response r;

    check_error( yrmcds_cnt_connect(&c, "localhost", 11215) );
    check_error( yrmcds_cnt_noop(&c, NULL) );
    check_error( yrmcds_cnt_recv(&c, &r) );
    check_response(&r);
    check_error( yrmcds_cnt_close(&c) );

    return 0;
}