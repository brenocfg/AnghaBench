#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* filename; TYPE_1__* meth; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* dso_load ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  DSO_METHOD ;
typedef  TYPE_2__ DSO ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_CTRL_SET_FLAGS ; 
 int /*<<< orphan*/  DSO_F_DSO_LOAD ; 
 int /*<<< orphan*/  DSO_R_CTRL_FAILED ; 
 int /*<<< orphan*/  DSO_R_DSO_ALREADY_LOADED ; 
 int /*<<< orphan*/  DSO_R_LOAD_FAILED ; 
 int /*<<< orphan*/  DSO_R_NO_FILENAME ; 
 int /*<<< orphan*/  DSO_R_SET_FILENAME_FAILED ; 
 int /*<<< orphan*/  DSO_R_UNSUPPORTED ; 
 scalar_t__ DSO_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSO_free (TYPE_2__*) ; 
 TYPE_2__* DSO_new_method (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSO_set_filename (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  DSOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

DSO *DSO_load(DSO *dso, const char *filename, DSO_METHOD *meth, int flags)
{
    DSO *ret;
    int allocated = 0;

    if (dso == NULL) {
        ret = DSO_new_method(meth);
        if (ret == NULL) {
            DSOerr(DSO_F_DSO_LOAD, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        allocated = 1;
        /* Pass the provided flags to the new DSO object */
        if (DSO_ctrl(ret, DSO_CTRL_SET_FLAGS, flags, NULL) < 0) {
            DSOerr(DSO_F_DSO_LOAD, DSO_R_CTRL_FAILED);
            goto err;
        }
    } else
        ret = dso;
    /* Don't load if we're currently already loaded */
    if (ret->filename != NULL) {
        DSOerr(DSO_F_DSO_LOAD, DSO_R_DSO_ALREADY_LOADED);
        goto err;
    }
    /*
     * filename can only be NULL if we were passed a dso that already has one
     * set.
     */
    if (filename != NULL)
        if (!DSO_set_filename(ret, filename)) {
            DSOerr(DSO_F_DSO_LOAD, DSO_R_SET_FILENAME_FAILED);
            goto err;
        }
    filename = ret->filename;
    if (filename == NULL) {
        DSOerr(DSO_F_DSO_LOAD, DSO_R_NO_FILENAME);
        goto err;
    }
    if (ret->meth->dso_load == NULL) {
        DSOerr(DSO_F_DSO_LOAD, DSO_R_UNSUPPORTED);
        goto err;
    }
    if (!ret->meth->dso_load(ret)) {
        DSOerr(DSO_F_DSO_LOAD, DSO_R_LOAD_FAILED);
        goto err;
    }
    /* Load succeeded */
    return ret;
 err:
    if (allocated)
        DSO_free(ret);
    return NULL;
}