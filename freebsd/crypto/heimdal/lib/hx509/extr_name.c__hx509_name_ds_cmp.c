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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  DirectoryString ;

/* Variables and functions */
 int dsstringprep (int /*<<< orphan*/  const*,int**,size_t*) ; 
 int /*<<< orphan*/  free (int*) ; 

int
_hx509_name_ds_cmp(const DirectoryString *ds1,
		   const DirectoryString *ds2,
		   int *diff)
{
    uint32_t *ds1lp, *ds2lp;
    size_t ds1len, ds2len, i;
    int ret;

    ret = dsstringprep(ds1, &ds1lp, &ds1len);
    if (ret)
	return ret;
    ret = dsstringprep(ds2, &ds2lp, &ds2len);
    if (ret) {
	free(ds1lp);
	return ret;
    }

    if (ds1len != ds2len)
	*diff = ds1len - ds2len;
    else {
	for (i = 0; i < ds1len; i++) {
	    *diff = ds1lp[i] - ds2lp[i];
	    if (*diff)
		break;
	}
    }
    free(ds1lp);
    free(ds2lp);

    return 0;
}