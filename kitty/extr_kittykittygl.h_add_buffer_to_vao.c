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
struct TYPE_3__ {int num_buffers; int* buffers; } ;
typedef  TYPE_1__ VAO ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int create_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static size_t
add_buffer_to_vao(ssize_t vao_idx, GLenum usage) {
    VAO* vao = vaos + vao_idx;
    if (vao->num_buffers >= sizeof(vao->buffers) / sizeof(vao->buffers[0])) {
        fatal("Too many buffers in a single VAO");
    }
    ssize_t buf = create_buffer(usage);
    vao->buffers[vao->num_buffers++] = buf;
    return vao->num_buffers - 1;
}