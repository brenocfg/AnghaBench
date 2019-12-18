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
typedef  int /*<<< orphan*/  ldns_dnssec_name ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_dnssec_name_free_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ldns_dnssec_name_free(ldns_dnssec_name *name)
{
  ldns_dnssec_name_free_internal(name, 0);
}