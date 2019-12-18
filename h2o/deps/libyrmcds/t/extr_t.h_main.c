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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * get_yrmcds (int /*<<< orphan*/ *) ; 
 scalar_t__ n_failures ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_main (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yrmcds_close (int /*<<< orphan*/ *) ; 

int main(int argc, char** argv) {
    yrmcds c_;
    yrmcds* c = get_yrmcds(&c_);
    if( c == NULL ) {
        fprintf(stderr, "No YRMCDS_HOST.  Skipped.\n");
        return 0;
    }

    test_main(c);
    yrmcds_close(c);

    if( n_failures > 0 ) {
        fprintf(stderr, "%d tests failed.\n", n_failures);
        return 1;
    }
    fprintf(stderr, "Passed.\n");
    return 0;
}