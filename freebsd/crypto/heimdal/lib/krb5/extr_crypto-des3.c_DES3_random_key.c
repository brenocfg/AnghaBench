#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {TYPE_1__ keyvalue; } ;
typedef  TYPE_2__ krb5_keyblock ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 scalar_t__ DES_is_weak_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_odd_parity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_generate_random_block (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
DES3_random_key(krb5_context context,
		krb5_keyblock *key)
{
    DES_cblock *k = key->keyvalue.data;
    do {
	krb5_generate_random_block(k, 3 * sizeof(DES_cblock));
	DES_set_odd_parity(&k[0]);
	DES_set_odd_parity(&k[1]);
	DES_set_odd_parity(&k[2]);
    } while(DES_is_weak_key(&k[0]) ||
	    DES_is_weak_key(&k[1]) ||
	    DES_is_weak_key(&k[2]));
}