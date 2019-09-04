#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; size_t data_len; } ;
typedef  TYPE_1__ yrmcds_response ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int write (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static void write_data(const yrmcds_response* r) {
    const char* p = r->data;
    size_t to_write = r->data_len;
    while( to_write > 0 ) {
        ssize_t n = write(STDOUT_FILENO, p, to_write);
        if( n == -1 ) return;
        p += n;
        to_write -= (size_t)n;
    }
    // writing a newline breaks data equality...
    //char nl = '\n';
    //write(STDOUT_FILENO, &nl, 1);
}