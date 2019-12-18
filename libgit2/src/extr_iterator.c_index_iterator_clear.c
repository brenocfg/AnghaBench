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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ index_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  iterator_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void index_iterator_clear(index_iterator *iter)
{
	iterator_clear(&iter->base);
}