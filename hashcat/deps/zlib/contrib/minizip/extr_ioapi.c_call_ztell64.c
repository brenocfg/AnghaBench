#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* ztell64_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  opaque; int /*<<< orphan*/ * zseek64_file; } ;
struct TYPE_5__ {scalar_t__ (* ztell32_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__ zfile_func64; } ;
typedef  TYPE_2__ zlib_filefunc64_32_def ;
typedef  int /*<<< orphan*/  voidpf ;
typedef  scalar_t__ uLong ;
typedef  scalar_t__ ZPOS64_T ;

/* Variables and functions */
 scalar_t__ MAXU32 ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ZPOS64_T call_ztell64 (const zlib_filefunc64_32_def* pfilefunc,voidpf filestream)
{
    if (pfilefunc->zfile_func64.zseek64_file != NULL)
        return (*(pfilefunc->zfile_func64.ztell64_file)) (pfilefunc->zfile_func64.opaque,filestream);
    else
    {
        uLong tell_uLong = (*(pfilefunc->ztell32_file))(pfilefunc->zfile_func64.opaque,filestream);
        if ((tell_uLong) == MAXU32)
            return (ZPOS64_T)-1;
        else
            return tell_uLong;
    }
}