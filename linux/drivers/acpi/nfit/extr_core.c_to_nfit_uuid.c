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
typedef  int /*<<< orphan*/  guid_t ;
typedef  enum nfit_uuids { ____Placeholder_nfit_uuids } nfit_uuids ;

/* Variables and functions */
 int /*<<< orphan*/  const* nfit_uuid ; 

const guid_t *to_nfit_uuid(enum nfit_uuids id)
{
	return &nfit_uuid[id];
}