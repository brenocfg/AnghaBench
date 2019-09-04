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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  glGetActiveUniformsiv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformIndices (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  program_id (int) ; 

__attribute__((used)) static inline GLint
get_uniform_information(int program, const char *name, GLenum information_type) {
    GLint q; GLuint t;
    static const char* names[] = {""};
    names[0] = name;
    GLuint pid = program_id(program);
    glGetUniformIndices(pid, 1, (void*)names, &t);
    glGetActiveUniformsiv(pid, 1, &t, information_type, &q);
    return q;
}