#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p ;
struct TYPE_5__ {int flags; int shutdown; int init; int /*<<< orphan*/ * ptr; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int BIO_CLOSE ; 
#define  BIO_CTRL_DUP 143 
#define  BIO_CTRL_EOF 142 
#define  BIO_CTRL_FLUSH 141 
#define  BIO_CTRL_GET_CLOSE 140 
#define  BIO_CTRL_INFO 139 
#define  BIO_CTRL_PENDING 138 
#define  BIO_CTRL_POP 137 
#define  BIO_CTRL_PUSH 136 
#define  BIO_CTRL_RESET 135 
#define  BIO_CTRL_SET_CLOSE 134 
#define  BIO_CTRL_WPENDING 133 
#define  BIO_C_FILE_SEEK 132 
#define  BIO_C_FILE_TELL 131 
#define  BIO_C_GET_FILE_PTR 130 
#define  BIO_C_SET_FILENAME 129 
#define  BIO_C_SET_FILE_PTR 128 
 int BIO_FLAGS_UPLINK ; 
 long BIO_FP_APPEND ; 
 long BIO_FP_READ ; 
 long BIO_FP_TEXT ; 
 long BIO_FP_WRITE ; 
 int /*<<< orphan*/  BIO_F_FILE_CTRL ; 
 int /*<<< orphan*/  BIO_R_BAD_FOPEN_MODE ; 
 int /*<<< orphan*/  BIO_clear_flags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EOF ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,...) ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  O_BINARY ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  SYS_F_FFLUSH ; 
 int /*<<< orphan*/  SYS_F_FOPEN ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ UP_feof (int /*<<< orphan*/ *) ; 
 int UP_fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ UP_fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UP_fsetmod (int /*<<< orphan*/ *,char) ; 
 long UP_ftell (int /*<<< orphan*/ *) ; 
 void* _IOB_ENTRIES ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _O_TEXT ; 
 int _fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _setmode (int,int /*<<< orphan*/ ) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_free (TYPE_1__*) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_last_sys_error () ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/ * openssl_fopen (void*,char*) ; 
 int /*<<< orphan*/  setmode (int,int /*<<< orphan*/ ) ; 
 void* stderr ; 
 void* stdin ; 
 void* stdout ; 

__attribute__((used)) static long file_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    long ret = 1;
    FILE *fp = (FILE *)b->ptr;
    FILE **fpp;
    char p[4];
    int st;

    switch (cmd) {
    case BIO_C_FILE_SEEK:
    case BIO_CTRL_RESET:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = (long)UP_fseek(b->ptr, num, 0);
        else
            ret = (long)fseek(fp, num, 0);
        break;
    case BIO_CTRL_EOF:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = (long)UP_feof(fp);
        else
            ret = (long)feof(fp);
        break;
    case BIO_C_FILE_TELL:
    case BIO_CTRL_INFO:
        if (b->flags & BIO_FLAGS_UPLINK)
            ret = UP_ftell(b->ptr);
        else
            ret = ftell(fp);
        break;
    case BIO_C_SET_FILE_PTR:
        file_free(b);
        b->shutdown = (int)num & BIO_CLOSE;
        b->ptr = ptr;
        b->init = 1;
# if BIO_FLAGS_UPLINK!=0
#  if defined(__MINGW32__) && defined(__MSVCRT__) && !defined(_IOB_ENTRIES)
#   define _IOB_ENTRIES 20
#  endif
        /* Safety net to catch purely internal BIO_set_fp calls */
#  if defined(_MSC_VER) && _MSC_VER>=1900
        if (ptr == stdin || ptr == stdout || ptr == stderr)
            BIO_clear_flags(b, BIO_FLAGS_UPLINK);
#  elif defined(_IOB_ENTRIES)
        if ((size_t)ptr >= (size_t)stdin &&
            (size_t)ptr < (size_t)(stdin + _IOB_ENTRIES))
            BIO_clear_flags(b, BIO_FLAGS_UPLINK);
#  endif
# endif
# ifdef UP_fsetmod
        if (b->flags & BIO_FLAGS_UPLINK)
            UP_fsetmod(b->ptr, (char)((num & BIO_FP_TEXT) ? 't' : 'b'));
        else
# endif
        {
# if defined(OPENSSL_SYS_WINDOWS)
            int fd = _fileno((FILE *)ptr);
            if (num & BIO_FP_TEXT)
                _setmode(fd, _O_TEXT);
            else
                _setmode(fd, _O_BINARY);
# elif defined(OPENSSL_SYS_MSDOS)
            int fd = fileno((FILE *)ptr);
            /* Set correct text/binary mode */
            if (num & BIO_FP_TEXT)
                _setmode(fd, _O_TEXT);
            /* Dangerous to set stdin/stdout to raw (unless redirected) */
            else {
                if (fd == STDIN_FILENO || fd == STDOUT_FILENO) {
                    if (isatty(fd) <= 0)
                        _setmode(fd, _O_BINARY);
                } else
                    _setmode(fd, _O_BINARY);
            }
# elif defined(OPENSSL_SYS_WIN32_CYGWIN)
            int fd = fileno((FILE *)ptr);
            if (!(num & BIO_FP_TEXT))
                setmode(fd, O_BINARY);
# endif
        }
        break;
    case BIO_C_SET_FILENAME:
        file_free(b);
        b->shutdown = (int)num & BIO_CLOSE;
        if (num & BIO_FP_APPEND) {
            if (num & BIO_FP_READ)
                OPENSSL_strlcpy(p, "a+", sizeof(p));
            else
                OPENSSL_strlcpy(p, "a", sizeof(p));
        } else if ((num & BIO_FP_READ) && (num & BIO_FP_WRITE))
            OPENSSL_strlcpy(p, "r+", sizeof(p));
        else if (num & BIO_FP_WRITE)
            OPENSSL_strlcpy(p, "w", sizeof(p));
        else if (num & BIO_FP_READ)
            OPENSSL_strlcpy(p, "r", sizeof(p));
        else {
            BIOerr(BIO_F_FILE_CTRL, BIO_R_BAD_FOPEN_MODE);
            ret = 0;
            break;
        }
# if defined(OPENSSL_SYS_MSDOS) || defined(OPENSSL_SYS_WINDOWS)
        if (!(num & BIO_FP_TEXT))
            OPENSSL_strlcat(p, "b", sizeof(p));
        else
            OPENSSL_strlcat(p, "t", sizeof(p));
# elif defined(OPENSSL_SYS_WIN32_CYGWIN)
        if (!(num & BIO_FP_TEXT))
            OPENSSL_strlcat(p, "b", sizeof(p));
# endif
        fp = openssl_fopen(ptr, p);
        if (fp == NULL) {
            SYSerr(SYS_F_FOPEN, get_last_sys_error());
            ERR_add_error_data(5, "fopen('", ptr, "','", p, "')");
            BIOerr(BIO_F_FILE_CTRL, ERR_R_SYS_LIB);
            ret = 0;
            break;
        }
        b->ptr = fp;
        b->init = 1;
        BIO_clear_flags(b, BIO_FLAGS_UPLINK); /* we did fopen -> we disengage
                                               * UPLINK */
        break;
    case BIO_C_GET_FILE_PTR:
        /* the ptr parameter is actually a FILE ** in this case. */
        if (ptr != NULL) {
            fpp = (FILE **)ptr;
            *fpp = (FILE *)b->ptr;
        }
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = (long)b->shutdown;
        break;
    case BIO_CTRL_SET_CLOSE:
        b->shutdown = (int)num;
        break;
    case BIO_CTRL_FLUSH:
        st = b->flags & BIO_FLAGS_UPLINK
                ? UP_fflush(b->ptr) : fflush((FILE *)b->ptr);
        if (st == EOF) {
            SYSerr(SYS_F_FFLUSH, get_last_sys_error());
            ERR_add_error_data(1, "fflush()");
            BIOerr(BIO_F_FILE_CTRL, ERR_R_SYS_LIB);
            ret = 0;
        }
        break;
    case BIO_CTRL_DUP:
        ret = 1;
        break;

    case BIO_CTRL_WPENDING:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_PUSH:
    case BIO_CTRL_POP:
    default:
        ret = 0;
        break;
    }
    return ret;
}