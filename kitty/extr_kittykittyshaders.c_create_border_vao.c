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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  BORDERS_PROGRAM ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT ; 
 int /*<<< orphan*/  add_attribute_to_vao (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,void*,int) ; 
 int /*<<< orphan*/  add_buffer_to_vao (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_vao () ; 

ssize_t
create_border_vao() {
    ssize_t vao_idx = create_vao();

    add_buffer_to_vao(vao_idx, GL_ARRAY_BUFFER);
    add_attribute_to_vao(BORDERS_PROGRAM, vao_idx, "rect",
            /*size=*/4, /*dtype=*/GL_UNSIGNED_INT, /*stride=*/sizeof(GLuint)*5, /*offset=*/0, /*divisor=*/1);
    add_attribute_to_vao(BORDERS_PROGRAM, vao_idx, "rect_color",
            /*size=*/1, /*dtype=*/GL_UNSIGNED_INT, /*stride=*/sizeof(GLuint)*5, /*offset=*/(void*)(sizeof(GLuint)*4), /*divisor=*/1);

    return vao_idx;
}