#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* opaque; int /*<<< orphan*/ * mutex; } ;
typedef  TYPE_1__ IJKFF_Pipenode ;

/* Variables and functions */
 int /*<<< orphan*/ * SDL_CreateMutex () ; 
 TYPE_1__* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

IJKFF_Pipenode *ffpipenode_alloc(size_t opaque_size)
{
    IJKFF_Pipenode *node = (IJKFF_Pipenode*) calloc(1, sizeof(IJKFF_Pipenode));
    if (!node)
        return NULL;

    node->opaque = calloc(1, opaque_size);
    if (!node->opaque) {
        free(node);
        return NULL;
    }

    node->mutex = SDL_CreateMutex();
    if (node->mutex == NULL) {
        free(node->opaque);
        free(node);
        return NULL;
    }

    return node;
}