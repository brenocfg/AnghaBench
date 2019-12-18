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
struct TYPE_3__ {int tls_done; scalar_t__ tlsalign; size_t tlsoffset; int /*<<< orphan*/  tlssize; } ;
typedef  TYPE_1__ Obj_Entry ;

/* Variables and functions */
 size_t calculate_first_tls_offset (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ calculate_tls_end (size_t,int /*<<< orphan*/ ) ; 
 size_t calculate_tls_offset (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t tls_last_offset ; 
 int /*<<< orphan*/  tls_last_size ; 
 scalar_t__ tls_static_max_align ; 
 scalar_t__ tls_static_space ; 

bool
allocate_tls_offset(Obj_Entry *obj)
{
    size_t off;

    if (obj->tls_done)
	return true;

    if (obj->tlssize == 0) {
	obj->tls_done = true;
	return true;
    }

    if (tls_last_offset == 0)
	off = calculate_first_tls_offset(obj->tlssize, obj->tlsalign);
    else
	off = calculate_tls_offset(tls_last_offset, tls_last_size,
				   obj->tlssize, obj->tlsalign);

    /*
     * If we have already fixed the size of the static TLS block, we
     * must stay within that size. When allocating the static TLS, we
     * leave a small amount of space spare to be used for dynamically
     * loading modules which use static TLS.
     */
    if (tls_static_space != 0) {
	if (calculate_tls_end(off, obj->tlssize) > tls_static_space)
	    return false;
    } else if (obj->tlsalign > tls_static_max_align) {
	    tls_static_max_align = obj->tlsalign;
    }

    tls_last_offset = obj->tlsoffset = off;
    tls_last_size = obj->tlssize;
    obj->tls_done = true;

    return true;
}