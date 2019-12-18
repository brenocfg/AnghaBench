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
struct TYPE_3__ {int /*<<< orphan*/ * cipher_suite; } ;
typedef  TYPE_1__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_cipher_suite_t ;

/* Variables and functions */

ptls_cipher_suite_t *ptls_get_cipher(ptls_t *tls)
{
    return tls->cipher_suite;
}