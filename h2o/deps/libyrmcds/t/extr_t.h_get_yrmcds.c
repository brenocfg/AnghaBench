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
typedef  int /*<<< orphan*/  yrmcds ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  check_error (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  yrmcds_connect (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static yrmcds* get_yrmcds(yrmcds* c) {
    const char* host = getenv("YRMCDS_HOST");
    if( host == NULL ) {
        return NULL;
    }
    uint16_t port = 11211;
    if( getenv("YRMCDS_PORT") ) {
        port = (uint16_t)atoi(getenv("YRMCDS_PORT"));
    }

    check_error( yrmcds_connect(c, host, port) );
    return c;
}