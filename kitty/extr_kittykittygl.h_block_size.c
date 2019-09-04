#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_UNIFORM_BLOCK_DATA_SIZE ; 
 int /*<<< orphan*/  glGetActiveUniformBlockiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* programs ; 

__attribute__((used)) static inline GLint
block_size(int program, GLuint block_index) {
    GLint ans;
    glGetActiveUniformBlockiv(programs[program].id, block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &ans);
    return ans;
}