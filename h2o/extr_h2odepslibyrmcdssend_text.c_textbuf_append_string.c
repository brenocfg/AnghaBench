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
struct TYPE_3__ {size_t pos; } ;
typedef  TYPE_1__ textbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 

__attribute__((used)) static inline void
textbuf_append_string(textbuf_t* buf, const char* s, size_t len) {
    memcpy(buf->pos, s, len);
    buf->pos += len;
}