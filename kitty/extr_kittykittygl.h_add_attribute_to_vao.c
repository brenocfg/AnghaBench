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
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  add_located_attribute_to_vao (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int attrib_location (int,char const*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 

__attribute__((used)) static inline void
add_attribute_to_vao(int p, ssize_t vao_idx, const char *name, GLint size, GLenum data_type, GLsizei stride, void *offset, GLuint divisor) {
    GLint aloc = attrib_location(p, name);
    if (aloc == -1) fatal("No attribute named: %s found in this program", name);
    add_located_attribute_to_vao(vao_idx, aloc, size, data_type, stride, offset, divisor);
}