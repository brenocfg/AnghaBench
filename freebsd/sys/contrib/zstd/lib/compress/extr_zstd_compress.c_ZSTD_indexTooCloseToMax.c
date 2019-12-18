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
struct TYPE_3__ {scalar_t__ base; scalar_t__ nextSrc; } ;
typedef  TYPE_1__ ZSTD_window_t ;

/* Variables and functions */
 size_t ZSTD_CURRENT_MAX ; 
 size_t ZSTD_INDEXOVERFLOW_MARGIN ; 

__attribute__((used)) static int ZSTD_indexTooCloseToMax(ZSTD_window_t w)
{
    return (size_t)(w.nextSrc - w.base) > (ZSTD_CURRENT_MAX - ZSTD_INDEXOVERFLOW_MARGIN);
}