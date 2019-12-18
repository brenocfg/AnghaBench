#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * cr_rights; } ;
typedef  TYPE_1__ const cap_rights_t ;

/* Variables and functions */
 unsigned int CAPARSIZE (TYPE_1__ const*) ; 
 unsigned int CAPARSIZE_MAX ; 
 unsigned int CAPARSIZE_MIN ; 
 scalar_t__ CAPVER (TYPE_1__ const*) ; 
 scalar_t__ CAP_RIGHTS_VERSION_00 ; 
 int /*<<< orphan*/  assert (int) ; 
 int cap_rights_is_valid (TYPE_1__ const*) ; 

cap_rights_t *
cap_rights_merge(cap_rights_t *dst, const cap_rights_t *src)
{
	unsigned int i, n;

	assert(CAPVER(dst) == CAP_RIGHTS_VERSION_00);
	assert(CAPVER(src) == CAP_RIGHTS_VERSION_00);
	assert(CAPVER(dst) == CAPVER(src));
	assert(cap_rights_is_valid(src));
	assert(cap_rights_is_valid(dst));

	n = CAPARSIZE(dst);
	assert(n >= CAPARSIZE_MIN && n <= CAPARSIZE_MAX);

	for (i = 0; i < n; i++)
		dst->cr_rights[i] |= src->cr_rights[i];

	assert(cap_rights_is_valid(src));
	assert(cap_rights_is_valid(dst));

	return (dst);
}