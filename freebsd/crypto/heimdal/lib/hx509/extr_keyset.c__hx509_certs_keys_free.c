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
typedef  scalar_t__ hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  hx509_private_key_free (scalar_t__*) ; 

void
_hx509_certs_keys_free(hx509_context context,
		       hx509_private_key *keys)
{
    int i;
    for (i = 0; keys[i]; i++)
	hx509_private_key_free(&keys[i]);
    free(keys);
}