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
struct TYPE_4__ {long (* zseek64_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ;int /*<<< orphan*/  opaque; } ;
struct TYPE_5__ {long (* zseek32_file ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ;TYPE_1__ zfile_func64; } ;
typedef  TYPE_2__ zlib_filefunc64_32_def ;
typedef  int /*<<< orphan*/  voidpf ;
typedef  scalar_t__ uLong ;
typedef  scalar_t__ ZPOS64_T ;

/* Variables and functions */
 long stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 long stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

long call_zseek64 (const zlib_filefunc64_32_def* pfilefunc,voidpf filestream, ZPOS64_T offset, int origin)
{
    if (pfilefunc->zfile_func64.zseek64_file != NULL)
        return (*(pfilefunc->zfile_func64.zseek64_file)) (pfilefunc->zfile_func64.opaque,filestream,offset,origin);
    else
    {
        uLong offsetTruncated = (uLong)offset;
        if (offsetTruncated != offset)
            return -1;
        else
            return (*(pfilefunc->zseek32_file))(pfilefunc->zfile_func64.opaque,filestream,offsetTruncated,origin);
    }
}