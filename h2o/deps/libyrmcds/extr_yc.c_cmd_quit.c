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
typedef  int /*<<< orphan*/  yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RESPONSE (int /*<<< orphan*/ *) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  yrmcds_quit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  yrmcds_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cmd_quit(int argc, char** argv, yrmcds* s) {
    yrmcds_response r[1];
    uint32_t serial;
    yrmcds_error e = yrmcds_quit(s, quiet, &serial);
    CHECK_ERROR(e);
    if( debug )
        fprintf(stderr, "request serial = %u\n", serial);
    if( ! quiet ) {
        e = yrmcds_recv(s, r);
        CHECK_ERROR(e);
        if( debug )
            print_response(r);
        CHECK_RESPONSE(r);
    }
    return 0;
}