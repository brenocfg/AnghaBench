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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_fs_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  alloc_buffer ; 
 int /*<<< orphan*/  file_pipe ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  read_stdin ; 
 int /*<<< orphan*/  stdin_pipe ; 
 int /*<<< orphan*/  stdout_pipe ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_fs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_pipe_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_pipe_open (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
    loop = uv_default_loop();

    uv_pipe_init(loop, &stdin_pipe, 0);
    uv_pipe_open(&stdin_pipe, 0);

    uv_pipe_init(loop, &stdout_pipe, 0);
    uv_pipe_open(&stdout_pipe, 1);
    
    uv_fs_t file_req;
    int fd = uv_fs_open(loop, &file_req, argv[1], O_CREAT | O_RDWR, 0644, NULL);
    uv_pipe_init(loop, &file_pipe, 0);
    uv_pipe_open(&file_pipe, fd);

    uv_read_start((uv_stream_t*)&stdin_pipe, alloc_buffer, read_stdin);

    uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}