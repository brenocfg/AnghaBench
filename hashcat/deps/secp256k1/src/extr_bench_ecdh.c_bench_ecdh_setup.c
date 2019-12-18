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
typedef  int /*<<< orphan*/  point ;
struct TYPE_2__ {int* scalar; int /*<<< orphan*/  point; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ bench_ecdh_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SECP256K1_FLAGS_TYPE_CONTEXT ; 
 int /*<<< orphan*/  secp256k1_context_create (int /*<<< orphan*/ ) ; 
 int secp256k1_ec_pubkey_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static void bench_ecdh_setup(void* arg) {
    int i;
    bench_ecdh_data *data = (bench_ecdh_data*)arg;
    const unsigned char point[] = {
        0x03,
        0x54, 0x94, 0xc1, 0x5d, 0x32, 0x09, 0x97, 0x06,
        0xc2, 0x39, 0x5f, 0x94, 0x34, 0x87, 0x45, 0xfd,
        0x75, 0x7c, 0xe3, 0x0e, 0x4e, 0x8c, 0x90, 0xfb,
        0xa2, 0xba, 0xd1, 0x84, 0xf8, 0x83, 0xc6, 0x9f
    };

    /* create a context with no capabilities */
    data->ctx = secp256k1_context_create(SECP256K1_FLAGS_TYPE_CONTEXT);
    for (i = 0; i < 32; i++) {
        data->scalar[i] = i + 1;
    }
    CHECK(secp256k1_ec_pubkey_parse(data->ctx, &data->point, point, sizeof(point)) == 1);
}