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
struct TYPE_3__ {char* xb_curp; } ;
typedef  TYPE_1__ xo_buffer_t ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CBOR_LEN16 ; 
 int /*<<< orphan*/  CBOR_LEN32 ; 
 int /*<<< orphan*/  CBOR_LEN64 ; 
 int /*<<< orphan*/  CBOR_LEN8 ; 
 unsigned long long CBOR_MINOR_MASK ; 

__attribute__((used)) static void
cbor_encode_uint (xo_buffer_t *xbp, uint64_t minor, unsigned limit)
{
    char *bp = xbp->xb_curp;
    int i, m;

    if (minor > (1ULL << 32)) {
	*bp++ |= CBOR_LEN64;
	m = 64;

    } else if (minor > (1<<16)) {
	*bp++ |= CBOR_LEN32;
	m = 32;

    } else if (minor > (1<<8)) {
	*bp++ |= CBOR_LEN16;
	m = 16;

    } else if (minor > limit) {
	*bp++ |= CBOR_LEN8;
	m = 8;
    } else {
	*bp++ |= minor & CBOR_MINOR_MASK;
	m = 0;
    }

    if (m) {
	for (i = m - 8; i >= 0; i -= 8)
	    *bp++ = minor >> i;
    }

    xbp->xb_curp = bp;
}