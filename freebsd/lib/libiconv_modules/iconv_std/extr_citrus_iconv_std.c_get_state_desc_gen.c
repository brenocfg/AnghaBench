#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
struct TYPE_4__ {TYPE_1__ generic; } ;
struct _stdenc_state_desc {TYPE_2__ u; } ;
struct _citrus_iconv_std_encoding {int /*<<< orphan*/  se_ps; int /*<<< orphan*/  se_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  _STDENC_SDID_GENERIC ; 
 int _stdenc_get_state_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct _stdenc_state_desc*) ; 

__attribute__((used)) static __inline int
get_state_desc_gen(struct _citrus_iconv_std_encoding *se, int *rstate)
{
	struct _stdenc_state_desc ssd;
	int ret;

	ret = _stdenc_get_state_desc(se->se_handle, se->se_ps,
	    _STDENC_SDID_GENERIC, &ssd);
	if (!ret)
		*rstate = ssd.u.generic.state;

	return (ret);
}