#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  param_name; } ;
typedef  TYPE_1__ MIME_PARAM ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mime_param_cmp(const MIME_PARAM *const *a,
                          const MIME_PARAM *const *b)
{
    if (!(*a)->param_name || !(*b)->param_name)
        return ! !(*a)->param_name - ! !(*b)->param_name;
    return strcmp((*a)->param_name, (*b)->param_name);
}