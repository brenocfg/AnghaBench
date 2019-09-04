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

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GRAPHICS_PROGRAM ; 
 int /*<<< orphan*/  add_attribute_to_vao (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_buffer_to_vao (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_vao () ; 

ssize_t
create_graphics_vao() {
    ssize_t vao_idx = create_vao();
    add_buffer_to_vao(vao_idx, GL_ARRAY_BUFFER);
    add_attribute_to_vao(GRAPHICS_PROGRAM, vao_idx, "src", 4, GL_FLOAT, 0, NULL, 0);
    return vao_idx;
}