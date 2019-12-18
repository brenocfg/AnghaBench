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
struct TYPE_4__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* zopen64_file ) (int /*<<< orphan*/ ,void const*,int) ;} ;
struct TYPE_5__ {TYPE_1__ zfile_func64; int /*<<< orphan*/  (* zopen32_file ) (int /*<<< orphan*/ ,char const*,int) ;} ;
typedef  TYPE_2__ zlib_filefunc64_32_def ;
typedef  int /*<<< orphan*/  voidpf ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,int) ; 

voidpf call_zopen64 (const zlib_filefunc64_32_def* pfilefunc,const void*filename,int mode)
{
    if (pfilefunc->zfile_func64.zopen64_file != NULL)
        return (*(pfilefunc->zfile_func64.zopen64_file)) (pfilefunc->zfile_func64.opaque,filename,mode);
    else
    {
        return (*(pfilefunc->zopen32_file))(pfilefunc->zfile_func64.opaque,(const char*)filename,mode);
    }
}