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
struct _citrus_stdenc_ops {int (* eo_init ) (struct _citrus_stdenc*,void const*,size_t,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * eo_get_state_desc; int /*<<< orphan*/ * eo_wctomb; int /*<<< orphan*/ * eo_mbtowc; int /*<<< orphan*/ * eo_cstomb; int /*<<< orphan*/ * eo_mbtocs; int /*<<< orphan*/ * eo_init_state; int /*<<< orphan*/ * eo_uninit; } ;
struct _citrus_stdenc {int /*<<< orphan*/ * ce_traits; struct _citrus_stdenc_ops* ce_ops; int /*<<< orphan*/ * ce_module; int /*<<< orphan*/ * ce_closure; } ;
typedef  int (* _citrus_stdenc_getops_t ) (struct _citrus_stdenc_ops*,int) ;
typedef  int /*<<< orphan*/ * _citrus_module_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _CITRUS_DEFAULT_STDENC_NAME ; 
 scalar_t__ _citrus_find_getops (int /*<<< orphan*/ *,char const*,char*) ; 
 int _citrus_load_module (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  _citrus_stdenc_close (struct _citrus_stdenc*) ; 
 struct _citrus_stdenc _citrus_stdenc_default ; 
 int errno ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (struct _citrus_stdenc_ops*,int) ; 
 int stub2 (struct _citrus_stdenc*,void const*,size_t,int /*<<< orphan*/ *) ; 

int
_citrus_stdenc_open(struct _citrus_stdenc * __restrict * __restrict rce,
    char const * __restrict encname, const void * __restrict variable,
    size_t lenvar)
{
	struct _citrus_stdenc *ce;
	_citrus_module_t handle;
	_citrus_stdenc_getops_t getops;
	int ret;

	if (!strcmp(encname, _CITRUS_DEFAULT_STDENC_NAME)) {
		*rce = &_citrus_stdenc_default;
		return (0);
	}
	ce = malloc(sizeof(*ce));
	if (ce == NULL) {
		ret = errno;
		goto bad;
	}
	ce->ce_ops = NULL;
	ce->ce_closure = NULL;
	ce->ce_module = NULL;
	ce->ce_traits = NULL;

	ret = _citrus_load_module(&handle, encname);
	if (ret)
		goto bad;

	ce->ce_module = handle;

	getops = (_citrus_stdenc_getops_t)_citrus_find_getops(ce->ce_module,
	    encname, "stdenc");
	if (getops == NULL) {
		ret = EINVAL;
		goto bad;
	}

	ce->ce_ops = (struct _citrus_stdenc_ops *)malloc(sizeof(*ce->ce_ops));
	if (ce->ce_ops == NULL) {
		ret = errno;
		goto bad;
	}

	ret = (*getops)(ce->ce_ops, sizeof(*ce->ce_ops));
	if (ret)
		goto bad;

	/* validation check */
	if (ce->ce_ops->eo_init == NULL ||
	    ce->ce_ops->eo_uninit == NULL ||
	    ce->ce_ops->eo_init_state == NULL ||
	    ce->ce_ops->eo_mbtocs == NULL ||
	    ce->ce_ops->eo_cstomb == NULL ||
	    ce->ce_ops->eo_mbtowc == NULL ||
	    ce->ce_ops->eo_wctomb == NULL ||
	    ce->ce_ops->eo_get_state_desc == NULL) {
		ret = EINVAL;
		goto bad;
	}

	/* allocate traits */
	ce->ce_traits = malloc(sizeof(*ce->ce_traits));
	if (ce->ce_traits == NULL) {
		ret = errno;
		goto bad;
	}
	/* init and get closure */
	ret = (*ce->ce_ops->eo_init)(ce, variable, lenvar, ce->ce_traits);
	if (ret)
		goto bad;

	*rce = ce;

	return (0);

bad:
	_citrus_stdenc_close(ce);
	return (ret);
}