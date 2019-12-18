#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* files; } ;
struct TYPE_3__ {void** files; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 TYPE_2__* current ; 
 void* open_fd_from_actual_fd (int /*<<< orphan*/ ) ; 

int create_piped_stdio() {
    if (!(current->files->files[0] = open_fd_from_actual_fd(STDIN_FILENO))) {
        return -1;
    }
    if (!(current->files->files[1] = open_fd_from_actual_fd(STDOUT_FILENO))) {
        return -1;
    }
    if (!(current->files->files[2] = open_fd_from_actual_fd(STDERR_FILENO))) {
        return -1;
    }
    return 0;
}