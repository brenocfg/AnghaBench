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
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 size_t OSSL_NELEM (TYPE_1__*) ; 
 TYPE_1__* cipher_data ; 
 int /*<<< orphan*/  destroy_cipher_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_all_cipher_methods(void)
{
    size_t i;

    for (i = 0; i < OSSL_NELEM(cipher_data); i++)
        destroy_cipher_method(cipher_data[i].nid);
}