#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ isc_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_DIR (TYPE_1__*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 

void
isc_dir_close(isc_dir_t *dir) {
       REQUIRE(VALID_DIR(dir) && dir->handle != NULL);

       (void)closedir(dir->handle);
       dir->handle = NULL;
}