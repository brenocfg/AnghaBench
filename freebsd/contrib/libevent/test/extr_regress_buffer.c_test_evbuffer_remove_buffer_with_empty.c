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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_add (struct evbuffer*,char*,int) ; 
 int /*<<< orphan*/  evbuffer_add_reference (struct evbuffer*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_remove_buffer (struct evbuffer*,struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_validate (struct evbuffer*) ; 
 int /*<<< orphan*/  no_cleanup ; 

__attribute__((used)) static void
test_evbuffer_remove_buffer_with_empty(void *ptr)
{
    struct evbuffer *src = evbuffer_new();
    struct evbuffer *dst = evbuffer_new();
    char buf[2];

    evbuffer_validate(src);
    evbuffer_validate(dst);

    /* setup the buffers */
    /* we need more data in src than we will move later */
    evbuffer_add_reference(src, buf, sizeof(buf), no_cleanup, NULL);
    evbuffer_add_reference(src, buf, sizeof(buf), no_cleanup, NULL);
    /* we need one buffer in dst and one empty buffer at the end */
    evbuffer_add(dst, buf, sizeof(buf));
    evbuffer_add_reference(dst, buf, 0, no_cleanup, NULL);

    evbuffer_validate(src);
    evbuffer_validate(dst);

    /* move three bytes over */
    evbuffer_remove_buffer(src, dst, 3);

    evbuffer_validate(src);
    evbuffer_validate(dst);

end:
    evbuffer_free(src);
    evbuffer_free(dst);
}