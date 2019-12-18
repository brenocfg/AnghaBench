#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* buf ) (void* const,size_t const) ;} ;

/* Variables and functions */
 TYPE_1__* implementation ; 
 int /*<<< orphan*/  randombytes_init_if_needed () ; 
 int /*<<< orphan*/  stub1 (void* const,size_t const) ; 

void
randombytes_buf(void * const buf, const size_t size)
{
    randombytes_init_if_needed();
    if (size > (size_t) 0U) {
        implementation->buf(buf, size);
    }
}