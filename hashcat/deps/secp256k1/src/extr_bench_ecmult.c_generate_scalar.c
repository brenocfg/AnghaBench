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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  secp256k1_sha256 ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  secp256k1_sha256_finalize (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  secp256k1_sha256_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_sha256_write (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void generate_scalar(uint32_t num, secp256k1_scalar* scalar) {
    secp256k1_sha256 sha256;
    unsigned char c[11] = {'e', 'c', 'm', 'u', 'l', 't', 0, 0, 0, 0};
    unsigned char buf[32];
    int overflow = 0;
    c[6] = num;
    c[7] = num >> 8;
    c[8] = num >> 16;
    c[9] = num >> 24;
    secp256k1_sha256_initialize(&sha256);
    secp256k1_sha256_write(&sha256, c, sizeof(c));
    secp256k1_sha256_finalize(&sha256, buf);
    secp256k1_scalar_set_b32(scalar, buf, &overflow);
    CHECK(!overflow);
}