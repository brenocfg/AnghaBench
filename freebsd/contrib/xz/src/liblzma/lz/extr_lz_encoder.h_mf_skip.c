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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  read_ahead; int /*<<< orphan*/  (* skip ) (TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ lzma_mf ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static inline void
mf_skip(lzma_mf *mf, uint32_t amount)
{
	if (amount != 0) {
		mf->skip(mf, amount);
		mf->read_ahead += amount;
	}
}