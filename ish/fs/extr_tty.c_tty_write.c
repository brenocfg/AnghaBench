#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int oflags; } ;
struct tty {TYPE_3__* driver; int /*<<< orphan*/  lock; TYPE_1__ termios; scalar_t__ hung_up; } ;
struct fd {int flags; struct tty* tty; } ;
typedef  int ssize_t ;
typedef  int dword_t ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int (* write ) (struct tty*,void const*,size_t,int) ;} ;

/* Variables and functions */
 int OCRNL_ ; 
 int ONLCR_ ; 
 int ONLRET_ ; 
 int OPOST_ ; 
 int O_NONBLOCK_ ; 
 int _EIO ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int stub1 (struct tty*,void const*,size_t,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t tty_write(struct fd *fd, const void *buf, size_t bufsize) {
    struct tty *tty = fd->tty;
    lock(&tty->lock);
    if (tty->hung_up) {
        unlock(&tty->lock);
        return _EIO;
    }

    bool blocking = !(fd->flags & O_NONBLOCK_);
    dword_t oflags = tty->termios.oflags;
    // we have to unlock it now to avoid lock ordering problems with ptys
    // the code below is safe because it only accesses tty->driver which is immutable
    // I reviewed real driver and ios driver and they're safe
    unlock(&tty->lock);

    int err = 0;
    char *postbuf = NULL;
    size_t postbufsize = bufsize;
    if (oflags & OPOST_) {
        postbuf = malloc(bufsize * 2);
        postbufsize = 0;
        const char *cbuf = buf;
        for (size_t i = 0; i < bufsize; i++) {
            char ch = cbuf[i];
            if (ch == '\r' && oflags & ONLRET_)
                continue;
            else if (ch == '\r' && oflags & OCRNL_)
                ch = '\n';
            else if (ch == '\n' && oflags & ONLCR_)
                postbuf[postbufsize++] = '\r';
            postbuf[postbufsize++] = ch;
        }
        buf = postbuf;
    }
    err = tty->driver->ops->write(tty, buf, postbufsize, blocking);
    if (postbuf)
        free(postbuf);
    if (err < 0)
        return err;
    return bufsize;
}