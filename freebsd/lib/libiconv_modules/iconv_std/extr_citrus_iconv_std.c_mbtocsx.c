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
struct iconv_hooks {int dummy; } ;
struct _citrus_iconv_std_encoding {int /*<<< orphan*/  se_ps; int /*<<< orphan*/  se_handle; } ;
typedef  int /*<<< orphan*/  _index_t ;
typedef  int /*<<< orphan*/  _csid_t ;

/* Variables and functions */
 int _stdenc_mbtocs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,size_t,int /*<<< orphan*/ ,size_t*,struct iconv_hooks*) ; 

__attribute__((used)) static __inline int
mbtocsx(struct _citrus_iconv_std_encoding *se,
    _csid_t *csid, _index_t *idx, char **s, size_t n, size_t *nresult,
    struct iconv_hooks *hooks)
{

	return (_stdenc_mbtocs(se->se_handle, csid, idx, s, n, se->se_ps,
			      nresult, hooks));
}