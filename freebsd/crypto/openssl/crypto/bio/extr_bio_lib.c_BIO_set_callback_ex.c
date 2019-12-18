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
struct TYPE_3__ {int /*<<< orphan*/  callback_ex; } ;
typedef  int /*<<< orphan*/  BIO_callback_fn_ex ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */

void BIO_set_callback_ex(BIO *b, BIO_callback_fn_ex cb)
{
    b->callback_ex = cb;
}