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
struct TYPE_3__ {scalar_t__ sz; int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ ThreadWriteData ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_twd (TYPE_1__*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  set_thread_name (char*) ; 

__attribute__((used)) static void*
thread_write(void *x) {
    ThreadWriteData *data = (ThreadWriteData*)x;
    set_thread_name("KittyWriteStdin");
    FILE *f = fdopen(data->fd, "w");
    if (fwrite(data->buf, 1, data->sz, f) != data->sz) {
        log_error("Failed to write all data");
    }
    fclose(f);
    free_twd(data);
    return 0;
}