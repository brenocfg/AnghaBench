#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_7__ {int /*<<< orphan*/ * stream; } ;
struct TYPE_8__ {void* flags; TYPE_1__ data; } ;
typedef  TYPE_2__ uv_stdio_container_t ;
struct TYPE_10__ {int stdio_count; char* file; char** args; int /*<<< orphan*/  exit_cb; TYPE_2__* stdio; } ;
struct TYPE_9__ {void* data; } ;

/* Variables and functions */
 void* UV_IGNORE ; 
 void* UV_INHERIT_STREAM ; 
 TYPE_3__ child_req ; 
 int /*<<< orphan*/  cleanup_handles ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  loop ; 
 TYPE_4__ options ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  uv_exepath (char*,size_t*) ; 
 int uv_spawn (int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 char* uv_strerror (int) ; 

void invoke_cgi_script(uv_tcp_t *client) {
    size_t size = 500;
    char path[size];
    uv_exepath(path, &size);
    strcpy(path + (strlen(path) - strlen("cgi")), "tick");

    char* args[2];
    args[0] = path;
    args[1] = NULL;

    /* ... finding the executable path and setting up arguments ... */

    options.stdio_count = 3;
    uv_stdio_container_t child_stdio[3];
    child_stdio[0].flags = UV_IGNORE;
    child_stdio[1].flags = UV_INHERIT_STREAM;
    child_stdio[1].data.stream = (uv_stream_t*) client;
    child_stdio[2].flags = UV_IGNORE;
    options.stdio = child_stdio;

    options.exit_cb = cleanup_handles;
    options.file = args[0];
    options.args = args;

    // Set this so we can close the socket after the child process exits.
    child_req.data = (void*) client;
    int r;
    if ((r = uv_spawn(loop, &child_req, &options))) {
        fprintf(stderr, "%s\n", uv_strerror(r));
        return;
    }
}