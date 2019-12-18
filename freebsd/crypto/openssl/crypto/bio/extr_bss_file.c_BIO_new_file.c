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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_CLOSE ; 
 int /*<<< orphan*/  BIO_FLAGS_UPLINK ; 
 int BIO_FP_TEXT ; 
 int /*<<< orphan*/  BIO_F_BIO_NEW_FILE ; 
 int /*<<< orphan*/  BIO_R_NO_SUCH_FILE ; 
 int /*<<< orphan*/  BIO_clear_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*,char*,char const*,char*) ; 
 int /*<<< orphan*/  SYS_F_FOPEN ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_last_sys_error () ; 
 int /*<<< orphan*/ * openssl_fopen (char const*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

BIO *BIO_new_file(const char *filename, const char *mode)
{
    BIO  *ret;
    FILE *file = openssl_fopen(filename, mode);
    int fp_flags = BIO_CLOSE;

    if (strchr(mode, 'b') == NULL)
        fp_flags |= BIO_FP_TEXT;

    if (file == NULL) {
        SYSerr(SYS_F_FOPEN, get_last_sys_error());
        ERR_add_error_data(5, "fopen('", filename, "','", mode, "')");
        if (errno == ENOENT
#ifdef ENXIO
            || errno == ENXIO
#endif
            )
            BIOerr(BIO_F_BIO_NEW_FILE, BIO_R_NO_SUCH_FILE);
        else
            BIOerr(BIO_F_BIO_NEW_FILE, ERR_R_SYS_LIB);
        return NULL;
    }
    if ((ret = BIO_new(BIO_s_file())) == NULL) {
        fclose(file);
        return NULL;
    }

    BIO_clear_flags(ret, BIO_FLAGS_UPLINK); /* we did fopen -> we disengage
                                             * UPLINK */
    BIO_set_fp(ret, file, fp_flags);
    return ret;
}