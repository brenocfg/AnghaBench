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
typedef  int /*<<< orphan*/ * voidpf ;
typedef  int uInt ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static voidpf
zalloc(voidpf opaque, uInt items, uInt size)
{
  apr_pool_t *pool = opaque;

  return apr_palloc(pool, items * size);
}