#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cpw_entry_data {int /*<<< orphan*/  password; scalar_t__ key_data; scalar_t__ random_password; scalar_t__ random_key; } ;
typedef  int /*<<< orphan*/  krb5_principal ;

/* Variables and functions */
 int set_key_data (int /*<<< orphan*/ ,scalar_t__) ; 
 int set_password (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_random_key (int /*<<< orphan*/ ) ; 
 int set_random_password (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_cpw_entry(krb5_principal principal, void *data)
{
    struct cpw_entry_data *e = data;

    if (e->random_key)
	return set_random_key (principal);
    else if (e->random_password)
	return set_random_password (principal);
    else if (e->key_data)
	return set_key_data (principal, e->key_data);
    else
	return set_password (principal, e->password);
}