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
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_input (struct tty*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void real_tty_read_thread(struct tty *tty) {
    char ch;
    for (;;) {
        int err = read(STDIN_FILENO, &ch, 1);
        if (err != 1) {
            printk("tty read returned %d\n", err);
            if (err < 0)
                printk("error: %s\n", strerror(errno));
            continue;
        }
        if (ch == '\x1c') {
            // ^\ (so ^C still works for emulated SIGINT)
            raise(SIGINT);
        }
        tty_input(tty, &ch, 1, 0);
    }
}