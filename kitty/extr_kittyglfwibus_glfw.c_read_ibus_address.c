#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  address_file_name; scalar_t__ address; int /*<<< orphan*/  address_file_mtime; } ;
typedef  TYPE_1__ _GLFWIBUSData ;
typedef  scalar_t__ GLFWbool ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ _glfw_strdup (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static inline GLFWbool
read_ibus_address(_GLFWIBUSData *ibus) {
    static char buf[1024];
    struct stat s;
    FILE *addr_file = fopen(ibus->address_file_name, "r");
    if (!addr_file) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to open IBUS address file: %s with error: %s", ibus->address_file_name, strerror(errno));
        return GLFW_FALSE;
    }
    int stat_result = fstat(fileno(addr_file), &s);
    GLFWbool found = GLFW_FALSE;
    while (fgets(buf, sizeof(buf), addr_file)) {
        if (strncmp(buf, "IBUS_ADDRESS=", sizeof("IBUS_ADDRESS=")-1) == 0) {
            size_t sz = strlen(buf);
            if (buf[sz-1] == '\n') buf[sz-1] = 0;
            if (buf[sz-2] == '\r') buf[sz-2] = 0;
            found = GLFW_TRUE;
            break;
        }
    }
    fclose(addr_file); addr_file = NULL;
    if (stat_result != 0) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Failed to stat IBUS address file: %s with error: %s", ibus->address_file_name, strerror(errno));
        return GLFW_FALSE;
    }
    ibus->address_file_mtime = s.st_mtime;
    if (found) {
        free((void*)ibus->address);
        ibus->address = _glfw_strdup(buf + sizeof("IBUS_ADDRESS=") - 1);
        return GLFW_TRUE;
    }
    _glfwInputError(GLFW_PLATFORM_ERROR, "Could not find IBUS_ADDRESS in %s", ibus->address_file_name);
    return GLFW_FALSE;
}