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
struct _citrus_iconv_std_encoding {scalar_t__ se_ps; int /*<<< orphan*/  se_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  _stdenc_init_state (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __inline void
init_encoding_state(struct _citrus_iconv_std_encoding *se)
{

	if (se->se_ps)
		_stdenc_init_state(se->se_handle, se->se_ps);
}