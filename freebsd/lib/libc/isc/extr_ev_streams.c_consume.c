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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {size_t ioDone; int /*<<< orphan*/  iovCurCount; TYPE_1__* iovCur; } ;
typedef  TYPE_2__ evStream ;
struct TYPE_4__ {scalar_t__ iov_len; void* iov_base; } ;

/* Variables and functions */

__attribute__((used)) static void
consume(evStream *str, size_t bytes) {
	while (bytes > 0U) {
		if (bytes < (size_t)str->iovCur->iov_len) {
			str->iovCur->iov_len -= bytes;
			str->iovCur->iov_base = (void *)
				((u_char *)str->iovCur->iov_base + bytes);
			str->ioDone += bytes;
			bytes = 0;
		} else {
			bytes -= str->iovCur->iov_len;
			str->ioDone += str->iovCur->iov_len;
			str->iovCur++;
			str->iovCurCount--;
		}
	}
}