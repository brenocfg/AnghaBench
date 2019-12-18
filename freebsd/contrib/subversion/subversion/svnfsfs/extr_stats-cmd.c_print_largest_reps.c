#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t count; TYPE_2__** changes; } ;
typedef  TYPE_3__ svn_fs_fs__largest_changes_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {scalar_t__ size; TYPE_1__* path; int /*<<< orphan*/  revision; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* svn__ui64toa_sep (scalar_t__,char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_largest_reps(svn_fs_fs__largest_changes_t *changes,
                   apr_pool_t *pool)
{
  apr_size_t i;
  for (i = 0; i < changes->count && changes->changes[i]->size; ++i)
    printf(_("%12s r%-8ld %s\n"),
           svn__ui64toa_sep(changes->changes[i]->size, ',', pool),
           changes->changes[i]->revision,
           changes->changes[i]->path->data);
}