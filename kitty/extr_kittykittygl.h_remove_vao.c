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
typedef  int ssize_t ;
struct TYPE_3__ {int num_buffers; scalar_t__ id; int /*<<< orphan*/ * buffers; } ;
typedef  TYPE_1__ VAO ;

/* Variables and functions */
 int /*<<< orphan*/  delete_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteVertexArrays (int,scalar_t__*) ; 
 TYPE_1__* vaos ; 

void
remove_vao(ssize_t vao_idx) {
    VAO *vao = vaos + vao_idx;
    while (vao->num_buffers) {
        vao->num_buffers--;
        delete_buffer(vao->buffers[vao->num_buffers]);
    }
    glDeleteVertexArrays(1, &(vao->id));
    vaos[vao_idx].id = 0;
}