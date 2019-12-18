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
struct TYPE_3__ {char* as_pointer; } ;
typedef  TYPE_1__ isc_symvalue_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (unsigned int,int) ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  isc_mem_free (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mctx ; 

__attribute__((used)) static void
undefine(char *key, unsigned int type, isc_symvalue_t value, void *arg) {
	UNUSED(arg);

	ATF_REQUIRE_EQ(type, 1);
	isc_mem_free(mctx, key);
	isc_mem_free(mctx, value.as_pointer);
}