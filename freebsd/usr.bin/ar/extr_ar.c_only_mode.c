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
struct bsdar {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
only_mode(struct bsdar *bsdar, const char *opt, const char *valid_modes)
{

	if (strchr(valid_modes, bsdar->mode) == NULL)
		bsdar_errc(bsdar, EX_USAGE, 0,
		    "Option %s is not permitted in mode -%c", opt, bsdar->mode);
}