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
struct TYPE_3__ {int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 void* CRYPTO_get_ex_data (int /*<<< orphan*/ *,int) ; 

void *SSL_CTX_get_ex_data(const SSL_CTX *s, int idx)
{
    return CRYPTO_get_ex_data(&s->ex_data, idx);
}