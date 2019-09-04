#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {size_t* buffers; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_UNIFORM_BUFFER ; 
 TYPE_2__* buffers ; 
 int /*<<< orphan*/  glBindBufferBase (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static void
bind_vao_uniform_buffer(ssize_t vao_idx, size_t bufnum, GLuint block_index) {
    ssize_t buf_idx = vaos[vao_idx].buffers[bufnum];
    glBindBufferBase(GL_UNIFORM_BUFFER, block_index, buffers[buf_idx].id);
}