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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  Key ;

/* Variables and functions */
 int /*<<< orphan*/  hdb_free_keys (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
_kadm5_free_keys (krb5_context context,
		  int len, Key *keys)
{
    hdb_free_keys(context, len, keys);
}