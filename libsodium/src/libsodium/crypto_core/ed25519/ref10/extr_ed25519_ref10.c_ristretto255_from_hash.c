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
typedef  int /*<<< orphan*/  ge25519_p3 ;
typedef  int /*<<< orphan*/  ge25519_p1p1 ;
typedef  int /*<<< orphan*/  ge25519_cached ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_frombytes (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  ge25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p1p1_to_p3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_p3_to_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ristretto255_elligator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ristretto255_p3_tobytes (unsigned char*,int /*<<< orphan*/ *) ; 

void
ristretto255_from_hash(unsigned char s[32], const unsigned char h[64])
{
    fe25519        r0, r1;
    ge25519_cached p1_cached;
    ge25519_p1p1   p_p1p1;
    ge25519_p3     p0, p1;
    ge25519_p3     p;

    fe25519_frombytes(r0, h);
    fe25519_frombytes(r1, h + 32);
    ristretto255_elligator(&p0, r0);
    ristretto255_elligator(&p1, r1);
    ge25519_p3_to_cached(&p1_cached, &p1);
    ge25519_add(&p_p1p1, &p0, &p1_cached);
    ge25519_p1p1_to_p3(&p, &p_p1p1);
    ristretto255_p3_tobytes(s, &p);
}