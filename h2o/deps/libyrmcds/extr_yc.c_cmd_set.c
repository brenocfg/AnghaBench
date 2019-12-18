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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RESPONSE (TYPE_1__*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  print_response (TYPE_1__*) ; 
 scalar_t__ quiet ; 
 size_t read_data (char*,char**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yrmcds_noop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  yrmcds_recv (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  yrmcds_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,size_t,int,int,scalar_t__,scalar_t__,int*) ; 

int cmd_set(int argc, char** argv, yrmcds* s) {
    if( argc < 2 || 5 < argc ) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }
    const char* key = argv[0];
    char* data = NULL;
    size_t data_len = read_data(argv[1], &data);
    if( data == NULL ) {
        fprintf(stderr, "Failed to read data.\n");
        return 2;
    }
    uint32_t expire = 0;
    uint32_t flags = 0;
    uint64_t cas = 0;

    if( argc > 2 )
        expire = (uint32_t)strtoull(argv[2], NULL, 0);
    if( argc > 3 )
        flags = (uint32_t)strtoull(argv[3], NULL, 0);
    if( argc > 4 )
        cas = (uint64_t)strtoull(argv[4], NULL, 0);

    yrmcds_response r[1];
    uint32_t serial;
    yrmcds_error e = yrmcds_set(s, key, strlen(key), data, data_len,
                                flags, expire, cas, quiet, &serial);
    free(data);
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