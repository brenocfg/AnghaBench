#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct krb5_key_state {TYPE_1__* ks_class; } ;
struct TYPE_2__ {size_t ec_checksumlen; } ;

/* Variables and functions */

__attribute__((used)) static size_t
token_length(struct krb5_key_state *key)
{

	return (16 + key->ks_class->ec_checksumlen);
}