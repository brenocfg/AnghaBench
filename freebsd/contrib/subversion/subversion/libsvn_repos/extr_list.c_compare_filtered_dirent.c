#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dirent; } ;
typedef  TYPE_2__ filtered_dirent_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_filtered_dirent(const void *lhs,
                        const void *rhs)
{
  const filtered_dirent_t *lhs_dirent = (const filtered_dirent_t *)lhs;
  const filtered_dirent_t *rhs_dirent = (const filtered_dirent_t *)rhs;

  return strcmp(lhs_dirent->dirent->name, rhs_dirent->dirent->name);
}