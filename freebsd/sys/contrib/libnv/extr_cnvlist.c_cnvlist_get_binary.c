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

/* Variables and functions */
 scalar_t__ NV_TYPE_BINARY ; 
 int /*<<< orphan*/  nvlist_report_missing (scalar_t__,int /*<<< orphan*/ ) ; 
 void const* nvpair_get_binary (void const*,size_t*) ; 
 int /*<<< orphan*/  nvpair_name (void const*) ; 
 scalar_t__ nvpair_type (void const*) ; 

const void *
cnvlist_get_binary(const void *cookie, size_t *sizep)
{

	if (nvpair_type(cookie) != NV_TYPE_BINARY)
		nvlist_report_missing(NV_TYPE_BINARY, nvpair_name(cookie));
	return (nvpair_get_binary(cookie, sizep));
}