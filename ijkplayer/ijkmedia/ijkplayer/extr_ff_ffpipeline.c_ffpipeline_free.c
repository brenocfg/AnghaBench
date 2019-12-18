#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* opaque; int /*<<< orphan*/  (* func_destroy ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ IJKFF_Pipeline ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void ffpipeline_free(IJKFF_Pipeline *pipeline)
{
    if (!pipeline)
        return;

    if (pipeline->func_destroy) {
        pipeline->func_destroy(pipeline);
    }

    free(pipeline->opaque);
    memset(pipeline, 0, sizeof(IJKFF_Pipeline));
    free(pipeline);
}