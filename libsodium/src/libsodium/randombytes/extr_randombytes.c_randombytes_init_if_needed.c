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
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  stir; int /*<<< orphan*/  random; int /*<<< orphan*/  implementation_name; } ;
typedef  TYPE_1__ randombytes_implementation ;

/* Variables and functions */
 TYPE_1__* RANDOMBYTES_DEFAULT_IMPLEMENTATION ; 
 TYPE_1__* implementation ; 
 int /*<<< orphan*/  javascript_buf ; 
 int /*<<< orphan*/  javascript_implementation_name ; 
 int /*<<< orphan*/  javascript_random ; 
 int /*<<< orphan*/  javascript_stir ; 
 int /*<<< orphan*/  randombytes_stir () ; 

__attribute__((used)) static void
randombytes_init_if_needed(void)
{
    if (implementation == NULL) {
#ifdef __EMSCRIPTEN__
        static randombytes_implementation javascript_implementation;
        javascript_implementation.implementation_name = javascript_implementation_name;
        javascript_implementation.random = javascript_random;
        javascript_implementation.stir = javascript_stir;
        javascript_implementation.buf = javascript_buf;
        implementation = &javascript_implementation;
#else
        implementation = RANDOMBYTES_DEFAULT_IMPLEMENTATION;
#endif
        randombytes_stir();
    }
}