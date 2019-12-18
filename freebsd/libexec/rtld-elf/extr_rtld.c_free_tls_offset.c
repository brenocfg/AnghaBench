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
struct TYPE_3__ {scalar_t__ tlssize; int /*<<< orphan*/  tlsoffset; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 scalar_t__ calculate_tls_end (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tls_last_offset ; 
 scalar_t__ tls_last_size ; 

void
free_tls_offset(Obj_Entry *obj)
{

    /*
     * If we were the last thing to allocate out of the static TLS
     * block, we give our space back to the 'allocator'. This is a
     * simplistic workaround to allow libGL.so.1 to be loaded and
     * unloaded multiple times.
     */
    if (calculate_tls_end(obj->tlsoffset, obj->tlssize)
	== calculate_tls_end(tls_last_offset, tls_last_size)) {
	tls_last_offset -= obj->tlssize;
	tls_last_size = 0;
    }
}