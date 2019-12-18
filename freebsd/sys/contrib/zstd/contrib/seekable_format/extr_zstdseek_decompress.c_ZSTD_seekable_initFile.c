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
struct TYPE_3__ {int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ ZSTD_seekable_customFile ;
typedef  int /*<<< orphan*/  ZSTD_seekable ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ZSTD_seekable_initAdvanced (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  ZSTD_seekable_read_FILE ; 
 int /*<<< orphan*/  ZSTD_seekable_seek_FILE ; 

size_t ZSTD_seekable_initFile(ZSTD_seekable* zs, FILE* src)
{
    ZSTD_seekable_customFile srcFile = {src, &ZSTD_seekable_read_FILE,
                                        &ZSTD_seekable_seek_FILE};
    return ZSTD_seekable_initAdvanced(zs, srcFile);
}