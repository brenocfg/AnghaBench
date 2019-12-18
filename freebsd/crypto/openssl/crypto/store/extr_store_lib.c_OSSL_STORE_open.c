#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scheme_copy ;
typedef  int /*<<< orphan*/  UI_METHOD ;
struct TYPE_8__ {void* post_process_data; int /*<<< orphan*/  post_process; void* ui_data; int /*<<< orphan*/  const* ui_method; int /*<<< orphan*/ * loader_ctx; TYPE_1__ const* loader; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open ) (TYPE_1__ const*,char const*,int /*<<< orphan*/  const*,void*) ;} ;
typedef  int /*<<< orphan*/  OSSL_STORE_post_process_info_fn ;
typedef  int /*<<< orphan*/  OSSL_STORE_LOADER_CTX ;
typedef  TYPE_1__ OSSL_STORE_LOADER ;
typedef  TYPE_2__ OSSL_STORE_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_last_mark () ; 
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char const*,int) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_OPEN ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ossl_store_get0_loader_int (char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__ const*,char const*,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

OSSL_STORE_CTX *OSSL_STORE_open(const char *uri, const UI_METHOD *ui_method,
                                void *ui_data,
                                OSSL_STORE_post_process_info_fn post_process,
                                void *post_process_data)
{
    const OSSL_STORE_LOADER *loader = NULL;
    OSSL_STORE_LOADER_CTX *loader_ctx = NULL;
    OSSL_STORE_CTX *ctx = NULL;
    char scheme_copy[256], *p, *schemes[2];
    size_t schemes_n = 0;
    size_t i;

    /*
     * Put the file scheme first.  If the uri does represent an existing file,
     * possible device name and all, then it should be loaded.  Only a failed
     * attempt at loading a local file should have us try something else.
     */
    schemes[schemes_n++] = "file";

    /*
     * Now, check if we have something that looks like a scheme, and add it
     * as a second scheme.  However, also check if there's an authority start
     * (://), because that will invalidate the previous file scheme.  Also,
     * check that this isn't actually the file scheme, as there's no point
     * going through that one twice!
     */
    OPENSSL_strlcpy(scheme_copy, uri, sizeof(scheme_copy));
    if ((p = strchr(scheme_copy, ':')) != NULL) {
        *p++ = '\0';
        if (strcasecmp(scheme_copy, "file") != 0) {
            if (strncmp(p, "//", 2) == 0)
                schemes_n--;         /* Invalidate the file scheme */
            schemes[schemes_n++] = scheme_copy;
        }
    }

    ERR_set_mark();

    /* Try each scheme until we find one that could open the URI */
    for (i = 0; loader_ctx == NULL && i < schemes_n; i++) {
        if ((loader = ossl_store_get0_loader_int(schemes[i])) != NULL)
            loader_ctx = loader->open(loader, uri, ui_method, ui_data);
    }
    if (loader_ctx == NULL)
        goto err;

    if ((ctx = OPENSSL_zalloc(sizeof(*ctx))) == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_OPEN, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    ctx->loader = loader;
    ctx->loader_ctx = loader_ctx;
    ctx->ui_method = ui_method;
    ctx->ui_data = ui_data;
    ctx->post_process = post_process;
    ctx->post_process_data = post_process_data;

    /*
     * If the attempt to open with the 'file' scheme loader failed and the
     * other scheme loader succeeded, the failure to open with the 'file'
     * scheme loader leaves an error on the error stack.  Let's remove it.
     */
    ERR_pop_to_mark();

    return ctx;

 err:
    ERR_clear_last_mark();
    if (loader_ctx != NULL) {
        /*
         * We ignore a returned error because we will return NULL anyway in
         * this case, so if something goes wrong when closing, that'll simply
         * just add another entry on the error stack.
         */
        (void)loader->close(loader_ctx);
    }
    return NULL;
}