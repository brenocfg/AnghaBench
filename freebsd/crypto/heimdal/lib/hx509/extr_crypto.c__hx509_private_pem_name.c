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
typedef  TYPE_2__* hx509_private_key ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {char const* pemtype; } ;

/* Variables and functions */

const char *
_hx509_private_pem_name(hx509_private_key key)
{
    return key->ops->pemtype;
}