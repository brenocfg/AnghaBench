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
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ svn_fnv1a_32__context_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  fnv1a_32 (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

void
svn_fnv1a_32__update(svn_fnv1a_32__context_t *context,
                     const void *data,
                     apr_size_t len)
{
  context->hash = fnv1a_32(context->hash, data, len);
}