#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ uv_fs_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct TYPE_7__ {size_t result; } ;

/* Variables and functions */
 char* buffer ; 
 int /*<<< orphan*/  crunch_away ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idler ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_2__ stdin_watcher ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_fs_read (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,void (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  uv_idle_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* uv_strerror (int /*<<< orphan*/ ) ; 

void on_type(uv_fs_t *req) {
    if (stdin_watcher.result > 0) {
        buffer[stdin_watcher.result] = '\0';
        printf("Typed %s\n", buffer);

        uv_buf_t buf = uv_buf_init(buffer, 1024);
        uv_fs_read(loop, &stdin_watcher, 0, &buf, 1, -1, on_type);
        uv_idle_start(&idler, crunch_away);
    }
    else if (stdin_watcher.result < 0) {
        fprintf(stderr, "error opening file: %s\n", uv_strerror(req->result));
    }
}