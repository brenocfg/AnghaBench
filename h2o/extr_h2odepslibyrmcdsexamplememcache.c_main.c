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
typedef  int /*<<< orphan*/  yrmcds_response ;
typedef  int /*<<< orphan*/  yrmcds ;

/* Variables and functions */
 int /*<<< orphan*/  check_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_connect (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  yrmcds_noop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int main(int argc, char** argv) {
    yrmcds c;
    yrmcds_response r;

    check_error( yrmcds_connect(&c, "localhost", 11211) );
    check_error( yrmcds_noop(&c, NULL) );
    check_error( yrmcds_recv(&c, &r) );
    check_response(&r);
    check_error( yrmcds_close(&c) );

    return 0;
}