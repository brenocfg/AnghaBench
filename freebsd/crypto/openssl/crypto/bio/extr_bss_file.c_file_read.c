#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ ptr; scalar_t__ init; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_UPLINK ; 
 int /*<<< orphan*/  BIO_F_FILE_READ ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  SYS_F_FREAD ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UP_ferror (int /*<<< orphan*/ *) ; 
 int UP_fread (char*,int,int,scalar_t__) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_last_sys_error () ; 

__attribute__((used)) static int file_read(BIO *b, char *out, int outl)
{
    int ret = 0;

    if (b->init && (out != NULL)) {
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = UP_fread(out, 1, (int)outl, b->ptr);
        else
            ret = fread(out, 1, (int)outl, (FILE *)b->ptr);
        if (ret == 0
            && (b->flags & BIO_FLAGS_UPLINK) ? UP_ferror((FILE *)b->ptr) :
                                               ferror((FILE *)b->ptr)) {
            SYSerr(SYS_F_FREAD, get_last_sys_error());
            BIOerr(BIO_F_FILE_READ, ERR_R_SYS_LIB);
            ret = -1;
        }
    }
    return ret;
}