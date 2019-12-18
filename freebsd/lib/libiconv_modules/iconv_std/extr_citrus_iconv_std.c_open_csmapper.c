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
struct _csmapper {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _csmapper_close (struct _csmapper*) ; 
 int _csmapper_get_dst_max (struct _csmapper*) ; 
 int _csmapper_get_src_max (struct _csmapper*) ; 
 scalar_t__ _csmapper_get_state_size (struct _csmapper*) ; 
 int _csmapper_open (struct _csmapper**,char const*,char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int
open_csmapper(struct _csmapper **rcm, const char *src, const char *dst,
    unsigned long *rnorm)
{
	struct _csmapper *cm;
	int ret;

	ret = _csmapper_open(&cm, src, dst, 0, rnorm);
	if (ret)
		return (ret);
	if (_csmapper_get_src_max(cm) != 1 || _csmapper_get_dst_max(cm) != 1 ||
	    _csmapper_get_state_size(cm) != 0) {
		_csmapper_close(cm);
		return (EINVAL);
	}

	*rcm = cm;

	return (0);
}