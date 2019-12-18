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
struct TYPE_4__ {int (* func_flush ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ IJKFF_Pipenode ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

int ffpipenode_flush(IJKFF_Pipenode *node)
{
    if (!node || !node->func_flush)
        return 0;

    return node->func_flush(node);
}