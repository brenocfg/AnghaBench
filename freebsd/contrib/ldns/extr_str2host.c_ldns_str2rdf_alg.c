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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_algorithms ; 
 int /*<<< orphan*/  ldns_str2rdf_mnemonic4int8 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*) ; 

ldns_status
ldns_str2rdf_alg(ldns_rdf **rd, const char *str)
{
	return ldns_str2rdf_mnemonic4int8(ldns_algorithms, rd, str);
}