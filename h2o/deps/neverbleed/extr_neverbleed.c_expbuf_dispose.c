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
struct expbuf_t {scalar_t__ capacity; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct expbuf_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void expbuf_dispose(struct expbuf_t *buf)
{
    if (buf->capacity != 0)
        OPENSSL_cleanse(buf->buf, buf->capacity);
    free(buf->buf);
    memset(buf, 0, sizeof(*buf));
}