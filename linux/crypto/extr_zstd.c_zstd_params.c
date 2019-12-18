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
typedef  int /*<<< orphan*/  ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_DEF_LEVEL ; 
 int /*<<< orphan*/  ZSTD_getParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ZSTD_parameters zstd_params(void)
{
	return ZSTD_getParams(ZSTD_DEF_LEVEL, 0, 0);
}