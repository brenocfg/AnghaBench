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
struct st_neverbleed_thread_data_t {int /*<<< orphan*/  fd; } ;
struct expbuf_t {int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  neverbleed_t ;

/* Variables and functions */
 int /*<<< orphan*/  dief (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  expbuf_dispose (struct expbuf_t*) ; 
 int /*<<< orphan*/  expbuf_push_num (struct expbuf_t*,int) ; 
 int /*<<< orphan*/  expbuf_push_str (struct expbuf_t*,char const*) ; 
 scalar_t__ expbuf_read (struct expbuf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ expbuf_shift_num (struct expbuf_t*,size_t*) ; 
 scalar_t__ expbuf_write (struct expbuf_t*,int /*<<< orphan*/ ) ; 
 struct st_neverbleed_thread_data_t* get_thread_data (int /*<<< orphan*/ *) ; 

int neverbleed_setuidgid(neverbleed_t *nb, const char *user, int change_socket_ownership)
{
    struct st_neverbleed_thread_data_t *thdata = get_thread_data(nb);
    struct expbuf_t buf = {NULL};
    size_t ret;

    expbuf_push_str(&buf, "setuidgid");
    expbuf_push_str(&buf, user);
    expbuf_push_num(&buf, change_socket_ownership);
    if (expbuf_write(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "write error" : "connection closed by daemon");
    expbuf_dispose(&buf);

    if (expbuf_read(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "read error" : "connection closed by daemon");
    if (expbuf_shift_num(&buf, &ret) != 0) {
        errno = 0;
        dief("failed to parse response");
    }
    expbuf_dispose(&buf);

    return (int)ret;
}