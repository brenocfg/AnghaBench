#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct untracked_cache {TYPE_1__ ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_ident_string () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ident_in_untracked(const struct untracked_cache *uc)
{
	/*
	 * Previous git versions may have saved many NUL separated
	 * strings in the "ident" field, but it is insane to manage
	 * many locations, so just take care of the first one.
	 */

	return !strcmp(uc->ident.buf, get_ident_string());
}