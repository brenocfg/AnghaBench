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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int ENOMEM ; 
 size_t MAX_LENGTH_CANON ; 
 int /*<<< orphan*/  canonical_reorder (int /*<<< orphan*/ *,size_t) ; 
 int combine (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int compat_decomp (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

int
_wind_stringprep_normalize(const uint32_t *in, size_t in_len,
			   uint32_t *out, size_t *out_len)
{
    size_t tmp_len;
    uint32_t *tmp;
    int ret;

    if (in_len == 0) {
	*out_len = 0;
	return 0;
    }

    tmp_len = in_len * 4;
    if (tmp_len < MAX_LENGTH_CANON)
	tmp_len = MAX_LENGTH_CANON;
    tmp = malloc(tmp_len * sizeof(uint32_t));
    if (tmp == NULL)
	return ENOMEM;

    ret = compat_decomp(in, in_len, tmp, &tmp_len);
    if (ret) {
	free(tmp);
	return ret;
    }
    canonical_reorder(tmp, tmp_len);
    ret = combine(tmp, tmp_len, out, out_len);
    free(tmp);
    return ret;
}