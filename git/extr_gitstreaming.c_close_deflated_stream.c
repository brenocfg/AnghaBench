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
struct git_istream {scalar_t__ z_state; int /*<<< orphan*/  z; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_inflate_end (int /*<<< orphan*/ *) ; 
 scalar_t__ z_used ; 

__attribute__((used)) static void close_deflated_stream(struct git_istream *st)
{
	if (st->z_state == z_used)
		git_inflate_end(&st->z);
}