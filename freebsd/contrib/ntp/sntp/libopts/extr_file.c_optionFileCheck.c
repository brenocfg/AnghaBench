#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tuFileMode ;
typedef  int teOptFileType ;
typedef  int /*<<< orphan*/  tOptions ;
struct TYPE_6__ {int fOptState; int /*<<< orphan*/ * optCookie; } ;
typedef  TYPE_1__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  AGFREE (int /*<<< orphan*/ *) ; 
 int FTYPE_MODE_EXIST_MASK ; 
#define  FTYPE_MODE_FOPEN_FP 132 
#define  FTYPE_MODE_MUST_EXIST 131 
#define  FTYPE_MODE_MUST_NOT_EXIST 130 
#define  FTYPE_MODE_NO_OPEN 129 
#define  FTYPE_MODE_OPEN_FD 128 
 int FTYPE_MODE_OPEN_MASK ; 
 int /*<<< orphan*/ * OPTPROC_EMIT_LIMIT ; 
 int /*<<< orphan*/ * OPTPROC_EMIT_USAGE ; 
 int OPTST_RESET ; 
 int /*<<< orphan*/  check_existence (int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fopen_file_fp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_file_fd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  option_usage_fp ; 
 scalar_t__ tab_skip_ct ; 
 scalar_t__ zFileCannotExist ; 
 scalar_t__ zFileMustExist ; 

void
optionFileCheck(tOptions * pOpts, tOptDesc * pOD,
                teOptFileType ftype, tuFileMode mode)
{
    if (pOpts <= OPTPROC_EMIT_LIMIT) {
        if (pOpts != OPTPROC_EMIT_USAGE)
            return;

        switch (ftype & FTYPE_MODE_EXIST_MASK) {
        case FTYPE_MODE_MUST_NOT_EXIST:
            fputs(zFileCannotExist + tab_skip_ct, option_usage_fp);
            break;

        case FTYPE_MODE_MUST_EXIST:
            fputs(zFileMustExist + tab_skip_ct, option_usage_fp);
            break;
        }
        return;
    }

    if ((pOD->fOptState & OPTST_RESET) != 0) {
        if (pOD->optCookie != NULL)
            AGFREE(pOD->optCookie);
        return;
    }

    check_existence(ftype, pOpts, pOD);

    switch (ftype & FTYPE_MODE_OPEN_MASK) {
    default:
    case FTYPE_MODE_NO_OPEN:  break;
    case FTYPE_MODE_OPEN_FD:  open_file_fd( pOpts, pOD, mode); break;
    case FTYPE_MODE_FOPEN_FP: fopen_file_fp(pOpts, pOD, mode); break;
    }
}