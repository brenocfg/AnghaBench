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
struct tmpl {scalar_t__ idx; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
has_tmpl(const struct tmpl *tmpl)
{
  return (tmpl->idx < RSTRING_LEN(tmpl->str));
}