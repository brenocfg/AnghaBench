#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct status_block {int dummy; } ;
struct ev_loop {int dummy; } ;
typedef  int /*<<< orphan*/  ev_io ;
struct TYPE_5__ {scalar_t__ hide_on_modifier; } ;
struct TYPE_4__ {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int,unsigned char*) ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct status_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocks ; 
 TYPE_1__ child ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  draw_bars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* get_buffer (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  main_loop ; 
 int /*<<< orphan*/  parse_json_header (TYPE_1__*,unsigned char*,int,unsigned int*) ; 
 int /*<<< orphan*/  read_flat_input (char*,int) ; 
 int /*<<< orphan*/  read_json_input (unsigned char*,int) ; 
 struct status_block* scalloc (int,int) ; 
 int /*<<< orphan*/  statusline_head ; 
 int /*<<< orphan*/  stdin_fd ; 
 int /*<<< orphan*/  stdin_io ; 
 int /*<<< orphan*/  stdin_io_cb ; 
 int /*<<< orphan*/  stop_child () ; 

__attribute__((used)) static void stdin_io_first_line_cb(struct ev_loop *loop, ev_io *watcher, int revents) {
    int rec;
    unsigned char *buffer = get_buffer(watcher, &rec);
    if (buffer == NULL)
        return;
    DLOG("Detecting input type based on buffer *%.*s*\n", rec, buffer);
    /* Detect whether this is JSON or plain text. */
    unsigned int consumed = 0;
    /* At the moment, we don’t care for the version. This might change
     * in the future, but for now, we just discard it. */
    parse_json_header(&child, buffer, rec, &consumed);
    if (child.version > 0) {
        /* If hide-on-modifier is set, we start of by sending the
         * child a SIGSTOP, because the bars aren't mapped at start */
        if (config.hide_on_modifier) {
            stop_child();
        }
        draw_bars(read_json_input(buffer + consumed, rec - consumed));
    } else {
        /* In case of plaintext, we just add a single block and change its
         * full_text pointer later. */
        struct status_block *new_block = scalloc(1, sizeof(struct status_block));
        TAILQ_INSERT_TAIL(&statusline_head, new_block, blocks);
        read_flat_input((char *)buffer, rec);
    }
    free(buffer);
    ev_io_stop(main_loop, stdin_io);
    ev_io_init(stdin_io, &stdin_io_cb, stdin_fd, EV_READ);
    ev_io_start(main_loop, stdin_io);
}