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
struct TYPE_2__ {int /*<<< orphan*/  kd_length; scalar_t__ kd_data; } ;
struct krb5_keyblock {TYPE_1__ kk_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_data (TYPE_1__*) ; 

__attribute__((used)) static void
delete_keyblock(struct krb5_keyblock *kk)
{
	if (kk->kk_key.kd_data)
		bzero(kk->kk_key.kd_data, kk->kk_key.kd_length);
	delete_data(&kk->kk_key);
}