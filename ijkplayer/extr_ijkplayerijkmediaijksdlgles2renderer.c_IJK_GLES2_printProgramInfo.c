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
typedef  int /*<<< orphan*/  buf_stack ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int GLsizei ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*,...) ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void IJK_GLES2_printProgramInfo(GLuint program)
{
    if (!program)
        return;

    GLint info_len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
    if (!info_len) {
        ALOGE("[GLES2][Program] empty info\n");
        return;
    }

    char    buf_stack[32];
    char   *buf_heap = NULL;
    char   *buf      = buf_stack;
    GLsizei buf_len  = sizeof(buf_stack) - 1;
    if (info_len > sizeof(buf_stack)) {
        buf_heap = (char*) malloc(info_len + 1);
        if (buf_heap) {
            buf     = buf_heap;
            buf_len = info_len;
        }
    }

    glGetProgramInfoLog(program, buf_len, NULL, buf);
    ALOGE("[GLES2][Program] error %s\n", buf);

    if (buf_heap)
        free(buf_heap);
}