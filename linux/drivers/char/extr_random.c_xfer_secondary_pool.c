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
struct entropy_store {size_t entropy_count; TYPE_1__* poolinfo; int /*<<< orphan*/  pull; } ;
struct TYPE_2__ {size_t poolfracbits; } ;

/* Variables and functions */
 int ENTROPY_SHIFT ; 
 int /*<<< orphan*/  _xfer_secondary_pool (struct entropy_store*,size_t) ; 

__attribute__((used)) static void xfer_secondary_pool(struct entropy_store *r, size_t nbytes)
{
	if (!r->pull ||
	    r->entropy_count >= (nbytes << (ENTROPY_SHIFT + 3)) ||
	    r->entropy_count > r->poolinfo->poolfracbits)
		return;

	_xfer_secondary_pool(r, nbytes);
}