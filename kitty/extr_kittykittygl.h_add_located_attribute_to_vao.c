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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int GLenum ;

/* Variables and functions */
#define  GL_BYTE 133 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_INT 132 
#define  GL_SHORT 131 
#define  GL_UNSIGNED_BYTE 130 
#define  GL_UNSIGNED_INT 129 
#define  GL_UNSIGNED_SHORT 128 
 int /*<<< orphan*/  bind_buffer (int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribDivisor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribIPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unbind_buffer (int) ; 
 TYPE_1__* vaos ; 

__attribute__((used)) static void
add_located_attribute_to_vao(ssize_t vao_idx, GLint aloc, GLint size, GLenum data_type, GLsizei stride, void *offset, GLuint divisor) {
    VAO *vao = vaos + vao_idx;
    if (!vao->num_buffers) fatal("You must create a buffer for this attribute first");
    ssize_t buf = vao->buffers[vao->num_buffers - 1];
    bind_buffer(buf);
    glEnableVertexAttribArray(aloc);
    switch(data_type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
            glVertexAttribIPointer(aloc, size, data_type, stride, offset);
            break;
        default:
            glVertexAttribPointer(aloc, size, data_type, GL_FALSE, stride, offset);
            break;
    }
    if (divisor) {
        glVertexAttribDivisor(aloc, divisor);
    }
    unbind_buffer(buf);
}