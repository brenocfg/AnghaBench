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
struct _citrus_iconv_std_encoding {int /*<<< orphan*/  se_ps; int /*<<< orphan*/  se_handle; } ;

/* Variables and functions */
 int _stdenc_put_state_reset (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static __inline int
put_state_resetx(struct _citrus_iconv_std_encoding *se, char *s, size_t n,
    size_t *nresult)
{

	return (_stdenc_put_state_reset(se->se_handle, s, n, se->se_ps, nresult));
}