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
struct _citrus_iconv_std_encoding {int /*<<< orphan*/  se_handle; int /*<<< orphan*/  se_pssaved; scalar_t__ se_ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  _stdenc_get_state_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
restore_encoding_state(struct _citrus_iconv_std_encoding *se)
{

	if (se->se_ps)
		memcpy(se->se_ps, se->se_pssaved,
		    _stdenc_get_state_size(se->se_handle));
}