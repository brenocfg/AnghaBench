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
typedef  int /*<<< orphan*/  IJKFF_Pipenode ;

/* Variables and functions */
 int /*<<< orphan*/  ffpipenode_free (int /*<<< orphan*/ *) ; 

void ffpipenode_free_p(IJKFF_Pipenode **node)
{
    if (!node)
        return;

    ffpipenode_free(*node);
    *node = NULL;
}