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
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 size_t ds_digest_size_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 

__attribute__((used)) static size_t
ds_digest_size_algo(struct ub_packed_rrset_key* k, size_t idx)
{
	return ds_digest_size_supported(ds_get_digest_algo(k, idx));
}