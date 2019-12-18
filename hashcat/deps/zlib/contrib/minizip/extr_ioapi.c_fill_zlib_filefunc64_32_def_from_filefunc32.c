#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ztell_file; int /*<<< orphan*/  zseek_file; int /*<<< orphan*/  opaque; int /*<<< orphan*/  zerror_file; int /*<<< orphan*/  zclose_file; int /*<<< orphan*/  zwrite_file; int /*<<< orphan*/  zread_file; int /*<<< orphan*/  zopen_file; } ;
typedef  TYPE_2__ zlib_filefunc_def ;
struct TYPE_6__ {int /*<<< orphan*/  opaque; int /*<<< orphan*/  zerror_file; int /*<<< orphan*/  zclose_file; int /*<<< orphan*/ * zseek64_file; int /*<<< orphan*/ * ztell64_file; int /*<<< orphan*/  zwrite_file; int /*<<< orphan*/  zread_file; int /*<<< orphan*/ * zopen64_file; } ;
struct TYPE_8__ {int /*<<< orphan*/  ztell32_file; int /*<<< orphan*/  zseek32_file; TYPE_1__ zfile_func64; int /*<<< orphan*/  zopen32_file; } ;
typedef  TYPE_3__ zlib_filefunc64_32_def ;

/* Variables and functions */

void fill_zlib_filefunc64_32_def_from_filefunc32(zlib_filefunc64_32_def* p_filefunc64_32,const zlib_filefunc_def* p_filefunc32)
{
    p_filefunc64_32->zfile_func64.zopen64_file = NULL;
    p_filefunc64_32->zopen32_file = p_filefunc32->zopen_file;
    p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
    p_filefunc64_32->zfile_func64.zread_file = p_filefunc32->zread_file;
    p_filefunc64_32->zfile_func64.zwrite_file = p_filefunc32->zwrite_file;
    p_filefunc64_32->zfile_func64.ztell64_file = NULL;
    p_filefunc64_32->zfile_func64.zseek64_file = NULL;
    p_filefunc64_32->zfile_func64.zclose_file = p_filefunc32->zclose_file;
    p_filefunc64_32->zfile_func64.zerror_file = p_filefunc32->zerror_file;
    p_filefunc64_32->zfile_func64.opaque = p_filefunc32->opaque;
    p_filefunc64_32->zseek32_file = p_filefunc32->zseek_file;
    p_filefunc64_32->ztell32_file = p_filefunc32->ztell_file;
}