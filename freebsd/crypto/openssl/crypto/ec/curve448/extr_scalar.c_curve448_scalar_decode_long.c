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
typedef  int /*<<< orphan*/  curve448_scalar_t ;

/* Variables and functions */
 size_t C448_SCALAR_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  curve448_scalar_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_scalar_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_scalar_decode (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  curve448_scalar_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_scalar_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curve448_scalar_one ; 
 int /*<<< orphan*/  curve448_scalar_zero ; 
 int /*<<< orphan*/  sc_montmul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_r2 ; 
 int /*<<< orphan*/  scalar_decode_short (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

void curve448_scalar_decode_long(curve448_scalar_t s,
                                 const unsigned char *ser, size_t ser_len)
{
    size_t i;
    curve448_scalar_t t1, t2;

    if (ser_len == 0) {
        curve448_scalar_copy(s, curve448_scalar_zero);
        return;
    }

    i = ser_len - (ser_len % C448_SCALAR_BYTES);
    if (i == ser_len)
        i -= C448_SCALAR_BYTES;

    scalar_decode_short(t1, &ser[i], ser_len - i);

    if (ser_len == sizeof(curve448_scalar_t)) {
        assert(i == 0);
        /* ham-handed reduce */
        curve448_scalar_mul(s, t1, curve448_scalar_one);
        curve448_scalar_destroy(t1);
        return;
    }

    while (i) {
        i -= C448_SCALAR_BYTES;
        sc_montmul(t1, t1, sc_r2);
        (void)curve448_scalar_decode(t2, ser + i);
        curve448_scalar_add(t1, t1, t2);
    }

    curve448_scalar_copy(s, t1);
    curve448_scalar_destroy(t1);
    curve448_scalar_destroy(t2);
}