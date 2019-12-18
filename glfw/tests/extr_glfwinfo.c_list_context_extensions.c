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
typedef  char GLubyte ;
typedef  int GLint ;

/* Variables and functions */
 int GLFW_OPENGL_API ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 char* get_api_name (int) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 char* glGetString (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetStringi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  putchar (char const) ; 

__attribute__((used)) static void list_context_extensions(int client, int major, int minor)
{
    printf("%s context extensions:\n", get_api_name(client));

    if (client == GLFW_OPENGL_API && major > 2)
    {
        GLint count;
        glGetIntegerv(GL_NUM_EXTENSIONS, &count);

        for (int i = 0;  i < count;  i++)
            printf(" %s\n", (const char*) glGetStringi(GL_EXTENSIONS, i));
    }
    else
    {
        const GLubyte* extensions = glGetString(GL_EXTENSIONS);
        while (*extensions != '\0')
        {
            putchar(' ');

            while (*extensions != '\0' && *extensions != ' ')
            {
                putchar(*extensions);
                extensions++;
            }

            while (*extensions == ' ')
                extensions++;

            putchar('\n');
        }
    }
}