#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ program; int /*<<< orphan*/  um4_mvp; void* av2_texcoord; void* av4_position; void* fragment_shader; void* vertex_shader; } ;
typedef  TYPE_1__ IJK_GLES2_Renderer ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  IJK_GLES2_Renderer_free (TYPE_1__*) ; 
 int /*<<< orphan*/  IJK_GLES2_checkError (char*) ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 char const* IJK_GLES2_getVertexShader_default () ; 
 void* IJK_GLES2_loadShader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  IJK_GLES2_printProgramInfo (scalar_t__) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,void*) ; 
 scalar_t__ glCreateProgram () ; 
 void* glGetAttribLocation (scalar_t__,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (scalar_t__,char*) ; 
 int /*<<< orphan*/  glLinkProgram (scalar_t__) ; 

IJK_GLES2_Renderer *IJK_GLES2_Renderer_create_base(const char *fragment_shader_source)
{
    assert(fragment_shader_source);

    IJK_GLES2_Renderer *renderer = (IJK_GLES2_Renderer *)calloc(1, sizeof(IJK_GLES2_Renderer));
    if (!renderer)
        goto fail;

    renderer->vertex_shader = IJK_GLES2_loadShader(GL_VERTEX_SHADER, IJK_GLES2_getVertexShader_default());
    if (!renderer->vertex_shader)
        goto fail;

    renderer->fragment_shader = IJK_GLES2_loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    if (!renderer->fragment_shader)
        goto fail;

    renderer->program = glCreateProgram();                          IJK_GLES2_checkError("glCreateProgram");
    if (!renderer->program)
        goto fail;

    glAttachShader(renderer->program, renderer->vertex_shader);     IJK_GLES2_checkError("glAttachShader(vertex)");
    glAttachShader(renderer->program, renderer->fragment_shader);   IJK_GLES2_checkError("glAttachShader(fragment)");
    glLinkProgram(renderer->program);                               IJK_GLES2_checkError("glLinkProgram");
    GLint link_status = GL_FALSE;
    glGetProgramiv(renderer->program, GL_LINK_STATUS, &link_status);
    if (!link_status)
        goto fail;


    renderer->av4_position = glGetAttribLocation(renderer->program, "av4_Position");                IJK_GLES2_checkError_TRACE("glGetAttribLocation(av4_Position)");
    renderer->av2_texcoord = glGetAttribLocation(renderer->program, "av2_Texcoord");                IJK_GLES2_checkError_TRACE("glGetAttribLocation(av2_Texcoord)");
    renderer->um4_mvp      = glGetUniformLocation(renderer->program, "um4_ModelViewProjection");    IJK_GLES2_checkError_TRACE("glGetUniformLocation(um4_ModelViewProjection)");

    return renderer;

fail:

    if (renderer && renderer->program)
        IJK_GLES2_printProgramInfo(renderer->program);

    IJK_GLES2_Renderer_free(renderer);
    return NULL;
}