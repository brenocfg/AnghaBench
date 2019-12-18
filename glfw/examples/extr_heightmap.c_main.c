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
typedef  unsigned int GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MAJOR ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MINOR ; 
 int GLFW_FALSE ; 
 int GLFW_OPENGL_CORE_PROFILE ; 
 int /*<<< orphan*/  GLFW_OPENGL_FORWARD_COMPAT ; 
 int /*<<< orphan*/  GLFW_OPENGL_PROFILE ; 
 int /*<<< orphan*/  GLFW_RESIZABLE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_LINES ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT ; 
 int MAP_NUM_LINES ; 
 int MAX_ITER ; 
 scalar_t__ NUM_ITER_AT_A_TIME ; 
 float aspect_ratio ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fragment_shader_text ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glDrawElements (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetUniformLocation (unsigned int,char*) ; 
 int /*<<< orphan*/  glUniformMatrix4fv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  glUseProgram (unsigned int) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_map () ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  make_mesh (unsigned int) ; 
 unsigned int make_shader_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float* modelview_matrix ; 
 float* projection_matrix ; 
 float tanf (float) ; 
 int /*<<< orphan*/  update_map (scalar_t__) ; 
 int /*<<< orphan*/  update_mesh () ; 
 int /*<<< orphan*/  vertex_shader_text ; 
 float view_angle ; 
 float z_far ; 
 float z_near ; 

int main(int argc, char** argv)
{
    GLFWwindow* window;
    int iter;
    double dt;
    double last_update_time;
    int frame;
    float f;
    GLint uloc_modelview;
    GLint uloc_project;
    int width, height;

    GLuint shader_program;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(800, 600, "GLFW OpenGL3 Heightmap demo", NULL, NULL);
    if (! window )
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    /* Register events callback */
    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    /* Prepare opengl resources for rendering */
    shader_program = make_shader_program(vertex_shader_text, fragment_shader_text);

    if (shader_program == 0u)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glUseProgram(shader_program);
    uloc_project   = glGetUniformLocation(shader_program, "project");
    uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
    f = 1.0f / tanf(view_angle / 2.0f);
    projection_matrix[0]  = f / aspect_ratio;
    projection_matrix[5]  = f;
    projection_matrix[10] = (z_far + z_near)/ (z_near - z_far);
    projection_matrix[11] = -1.0f;
    projection_matrix[14] = 2.0f * (z_far * z_near) / (z_near - z_far);
    glUniformMatrix4fv(uloc_project, 1, GL_FALSE, projection_matrix);

    /* Set the camera position */
    modelview_matrix[12]  = -5.0f;
    modelview_matrix[13]  = -5.0f;
    modelview_matrix[14]  = -20.0f;
    glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix);

    /* Create mesh data */
    init_map();
    make_mesh(shader_program);

    /* Create vao + vbo to store the mesh */
    /* Create the vbo to store all the information for the grid and the height */

    /* setup the scene ready for rendering */
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* main loop */
    frame = 0;
    iter = 0;
    last_update_time = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        ++frame;
        /* render the next frame */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_LINES, 2* MAP_NUM_LINES , GL_UNSIGNED_INT, 0);

        /* display and process events through callbacks */
        glfwSwapBuffers(window);
        glfwPollEvents();
        /* Check the frame rate and update the heightmap if needed */
        dt = glfwGetTime();
        if ((dt - last_update_time) > 0.2)
        {
            /* generate the next iteration of the heightmap */
            if (iter < MAX_ITER)
            {
                update_map(NUM_ITER_AT_A_TIME);
                update_mesh();
                iter += NUM_ITER_AT_A_TIME;
            }
            last_update_time = dt;
            frame = 0;
        }
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}