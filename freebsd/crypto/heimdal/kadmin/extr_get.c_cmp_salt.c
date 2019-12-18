#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {size_t salttype; TYPE_1__ saltvalue; } ;
typedef  TYPE_2__ krb5_salt ;
struct TYPE_8__ {int /*<<< orphan*/ * key_data_contents; scalar_t__* key_data_length; scalar_t__* key_data_type; } ;
typedef  TYPE_3__ krb5_key_data ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
cmp_salt (const krb5_salt *salt, const krb5_key_data *k)
{
    if (salt->salttype != (size_t)k->key_data_type[1])
	return 1;
    if (salt->saltvalue.length != (size_t)k->key_data_length[1])
	return 1;
    return memcmp (salt->saltvalue.data, k->key_data_contents[1],
		   salt->saltvalue.length);
}