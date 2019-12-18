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
struct TYPE_2__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_DECORATED ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_FOCUS_ON_SHOW ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  GLFW_VISIBLE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 TYPE_1__* colors ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 int /*<<< orphan*/  glfwGetWindowFrameSize (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowPos (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  glfwShowWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/ * titles ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char** argv)
{
    int i, ch;
    int decorated = GLFW_FALSE;
    int focusOnShow = GLFW_TRUE;
    int running = GLFW_TRUE;
    GLFWwindow* windows[4];

    while ((ch = getopt(argc, argv, "bfh")) != -1)
    {
        switch (ch)
        {
            case 'b':
                decorated = GLFW_TRUE;
                break;
            case 'f':
                focusOnShow = GLFW_FALSE;
                break;
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_DECORATED, decorated);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    for (i = 0;  i < 4;  i++)
    {
        int left, top, right, bottom;
        if (i)
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, focusOnShow);

        windows[i] = glfwCreateWindow(200, 200, titles[i], NULL, NULL);
        if (!windows[i])
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetKeyCallback(windows[i], key_callback);

        glfwMakeContextCurrent(windows[i]);
        gladLoadGL(glfwGetProcAddress);
        glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);

        glfwGetWindowFrameSize(windows[i], &left, &top, &right, &bottom);
        glfwSetWindowPos(windows[i],
                         100 + (i & 1) * (200 + left + right),
                         100 + (i >> 1) * (200 + top + bottom));
    }

    for (i = 0;  i < 4;  i++)
        glfwShowWindow(windows[i]);

    while (running)
    {
        for (i = 0;  i < 4;  i++)
        {
            glfwMakeContextCurrent(windows[i]);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(windows[i]);

            if (glfwWindowShouldClose(windows[i]))
                running = GLFW_FALSE;
        }

        glfwWaitEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}