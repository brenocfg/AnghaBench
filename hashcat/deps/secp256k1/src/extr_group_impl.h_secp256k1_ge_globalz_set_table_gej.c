#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ secp256k1_gej ;
struct TYPE_8__ {scalar_t__ infinity; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_fe ;

/* Variables and functions */
 int /*<<< orphan*/  secp256k1_fe_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize_weak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej_zinv (TYPE_2__*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void secp256k1_ge_globalz_set_table_gej(size_t len, secp256k1_ge *r, secp256k1_fe *globalz, const secp256k1_gej *a, const secp256k1_fe *zr) {
    size_t i = len - 1;
    secp256k1_fe zs;

    if (len > 0) {
        /* The z of the final point gives us the "global Z" for the table. */
        r[i].x = a[i].x;
        r[i].y = a[i].y;
        /* Ensure all y values are in weak normal form for fast negation of points */
        secp256k1_fe_normalize_weak(&r[i].y);
        *globalz = a[i].z;
        r[i].infinity = 0;
        zs = zr[i];

        /* Work our way backwards, using the z-ratios to scale the x/y values. */
        while (i > 0) {
            if (i != len - 1) {
                secp256k1_fe_mul(&zs, &zs, &zr[i]);
            }
            i--;
            secp256k1_ge_set_gej_zinv(&r[i], &a[i], &zs);
        }
    }
}