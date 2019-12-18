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
struct TYPE_2__ {int /*<<< orphan*/  scalar; int /*<<< orphan*/  point; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ bench_ecdh_data ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 int secp256k1_ecdh (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bench_ecdh(void* arg) {
    int i;
    unsigned char res[32];
    bench_ecdh_data *data = (bench_ecdh_data*)arg;

    for (i = 0; i < 20000; i++) {
        CHECK(secp256k1_ecdh(data->ctx, res, &data->point, data->scalar, NULL, NULL) == 1);
    }
}