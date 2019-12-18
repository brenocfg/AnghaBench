#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  entropy; } ;
struct TYPE_5__ {TYPE_1__ pool; } ;
typedef  TYPE_2__ isc_entropy_t ;

/* Variables and functions */
 scalar_t__ ISC_MIN (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
subtract_entropy(isc_entropy_t *ent, isc_uint32_t entropy) {
	entropy = ISC_MIN(entropy, ent->pool.entropy);
	ent->pool.entropy -= entropy;
}