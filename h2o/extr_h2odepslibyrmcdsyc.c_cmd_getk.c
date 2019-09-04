#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int serial; } ;
typedef  TYPE_1__ yrmcds_response ;
typedef  int /*<<< orphan*/  yrmcds_error ;
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RESPONSE (TYPE_1__*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_response (TYPE_1__*) ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  write_data (TYPE_1__*) ; 
 int /*<<< orphan*/  yrmcds_getk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  yrmcds_noop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  yrmcds_recv (int /*<<< orphan*/ *,TYPE_1__*) ; 

int cmd_getk(int argc, char** argv, yrmcds* s) {
    if( argc != 1 ) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }
    yrmcds_response r[1];
    uint32_t serial;
    yrmcds_error e = yrmcds_getk(s, argv[0], strlen(argv[0]), quiet, &serial);
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
    write_data(r);
    return 0;
}