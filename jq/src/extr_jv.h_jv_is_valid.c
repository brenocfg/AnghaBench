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
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_INVALID ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jv_is_valid(jv x) { return jv_get_kind(x) != JV_KIND_INVALID; }