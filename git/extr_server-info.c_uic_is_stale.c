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
struct update_info_ctx {int /*<<< orphan*/ * old_fp; } ;

/* Variables and functions */

__attribute__((used)) static int uic_is_stale(const struct update_info_ctx *uic)
{
	return uic->old_fp == NULL;
}