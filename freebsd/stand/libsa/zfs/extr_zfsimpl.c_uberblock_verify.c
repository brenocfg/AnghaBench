#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ ub_magic; int /*<<< orphan*/  ub_version; } ;
typedef  TYPE_1__ uberblock_t ;

/* Variables and functions */
 scalar_t__ BSWAP_64 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPA_VERSION_IS_SUPPORTED (int /*<<< orphan*/ ) ; 
 scalar_t__ UBERBLOCK_MAGIC ; 
 int /*<<< orphan*/  byteswap_uint64_array (TYPE_1__*,int) ; 

__attribute__((used)) static int
uberblock_verify(uberblock_t *ub)
{
	if (ub->ub_magic == BSWAP_64((uint64_t)UBERBLOCK_MAGIC)) {
		byteswap_uint64_array(ub, sizeof (uberblock_t));
	}

	if (ub->ub_magic != UBERBLOCK_MAGIC ||
	    !SPA_VERSION_IS_SUPPORTED(ub->ub_version))
		return (EINVAL);

	return (0);
}