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
typedef  scalar_t__ yrmcds_error ;

/* Variables and functions */
 scalar_t__ YRMCDS_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* yrmcds_strerror (scalar_t__) ; 

__attribute__((used)) static void check_error(yrmcds_error e) {
    if( e == YRMCDS_OK )
        return;

    fprintf(stderr, "yrmcds error: %s\n", yrmcds_strerror(e));
    exit(1);
}