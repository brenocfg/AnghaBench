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
struct TYPE_3__ {int /*<<< orphan*/ * engine; } ;
typedef  int /*<<< orphan*/  ENGINE ;
typedef  TYPE_1__ EC_KEY ;

/* Variables and functions */

ENGINE *EC_KEY_get0_engine(const EC_KEY *eckey)
{
    return eckey->engine;
}