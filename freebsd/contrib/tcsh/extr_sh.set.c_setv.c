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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  set1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shvhed ; 
 int /*<<< orphan*/ ** xmalloc (int) ; 

void
setv(const Char *var, Char *val, int flags)
{
    Char **vec = xmalloc(2 * sizeof(Char **));

    vec[0] = val;
    vec[1] = 0;
    set1(var, vec, &shvhed, flags);
}