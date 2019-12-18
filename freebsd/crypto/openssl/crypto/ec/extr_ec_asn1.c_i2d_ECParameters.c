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
struct TYPE_3__ {int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_I2D_ECPARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int i2d_ECPKParameters (int /*<<< orphan*/ ,unsigned char**) ; 

int i2d_ECParameters(EC_KEY *a, unsigned char **out)
{
    if (a == NULL) {
        ECerr(EC_F_I2D_ECPARAMETERS, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    return i2d_ECPKParameters(a->group, out);
}