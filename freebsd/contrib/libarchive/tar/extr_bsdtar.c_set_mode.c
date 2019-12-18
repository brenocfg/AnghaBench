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
struct bsdtar {char mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,char,char) ; 

__attribute__((used)) static void
set_mode(struct bsdtar *bsdtar, char opt)
{
	if (bsdtar->mode != '\0' && bsdtar->mode != opt)
		lafe_errc(1, 0,
		    "Can't specify both -%c and -%c", opt, bsdtar->mode);
	bsdtar->mode = opt;
}