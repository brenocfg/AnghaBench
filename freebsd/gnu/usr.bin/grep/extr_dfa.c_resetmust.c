#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* left; char* right; char* is; int /*<<< orphan*/  in; } ;
typedef  TYPE_1__ must ;

/* Variables and functions */
 int /*<<< orphan*/  freelist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
resetmust (must *mp)
{
  mp->left[0] = mp->right[0] = mp->is[0] = '\0';
  freelist(mp->in);
}