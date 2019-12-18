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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 long fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwUpdateGamepadMappings (char*) ; 
 char* malloc (long) ; 

__attribute__((used)) static void drop_callback(GLFWwindow* window, int count, const char* paths[])
{
    int i;

    for (i = 0;  i < count;  i++)
    {
        long size;
        char* text;
        FILE* stream = fopen(paths[i], "rb");
        if (!stream)
            continue;

        fseek(stream, 0, SEEK_END);
        size = ftell(stream);
        fseek(stream, 0, SEEK_SET);

        text = malloc(size + 1);
        text[size] = '\0';
        if (fread(text, 1, size, stream) == size)
            glfwUpdateGamepadMappings(text);

        free(text);
        fclose(stream);
    }
}