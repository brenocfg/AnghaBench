#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int serial; } ;
typedef  TYPE_1__ yrmcds_response ;
typedef  int /*<<< orphan*/  yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RESPONSE (TYPE_1__*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_response (TYPE_1__*) ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yrmcds_flush (int /*<<< orphan*/ *,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  yrmcds_noop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  yrmcds_recv (int /*<<< orphan*/ *,TYPE_1__*) ; 

int cmd_flush(int argc, char** argv, yrmcds* s) {
    uint32_t delay = 0;
    if( argc == 1 )
        delay = (uint32_t)strtoull(argv[0], NULL, 0);

    yrmcds_response r[1];
    uint32_t serial;
    yrmcds_error e = yrmcds_flush(s, delay, quiet, &serial);
    CHECK_ERROR(e);
    if( quiet ) {
        e = yrmcds_noop(s, &serial);
        CHECK_ERROR(e);
    }
    if( debug )
        fprintf(stderr, "request serial = %u\n", serial);
    while( 1 ) {
        e = yrmcds_recv(s, r);
        CHECK_ERROR(e);
        if( debug )
            print_response(r);
        CHECK_RESPONSE(r);
        if( r->serial == serial )
            break;
    }
    return 0;
}