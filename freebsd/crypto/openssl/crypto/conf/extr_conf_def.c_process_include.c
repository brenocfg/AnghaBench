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
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  OPENSSL_DIR_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new_file (char*,char*) ; 
 int /*<<< orphan*/  CONF_F_PROCESS_INCLUDE ; 
 int /*<<< orphan*/  CONF_R_RECURSIVE_DIRECTORY_INCLUDE ; 
 int /*<<< orphan*/  CONFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*) ; 
 int /*<<< orphan*/  SYS_F_STAT ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * get_next_file (char*,int /*<<< orphan*/ **) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static BIO *process_include(char *include, OPENSSL_DIR_CTX **dirctx,
                            char **dirpath)
{
    struct stat st = { 0 };
    BIO *next;

    if (stat(include, &st) < 0) {
        SYSerr(SYS_F_STAT, errno);
        ERR_add_error_data(1, include);
        /* missing include file is not fatal error */
        return NULL;
    }

    if (S_ISDIR(st.st_mode)) {
        if (*dirctx != NULL) {
            CONFerr(CONF_F_PROCESS_INCLUDE,
                    CONF_R_RECURSIVE_DIRECTORY_INCLUDE);
            ERR_add_error_data(1, include);
            return NULL;
        }
        /* a directory, load its contents */
        if ((next = get_next_file(include, dirctx)) != NULL)
            *dirpath = include;
        return next;
    }

    next = BIO_new_file(include, "r");
    return next;
}