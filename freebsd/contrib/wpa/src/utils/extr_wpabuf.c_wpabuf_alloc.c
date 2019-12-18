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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf_trace {int /*<<< orphan*/  magic; } ;
struct wpabuf {size_t size; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPABUF_MAGIC ; 
 void* os_zalloc (int) ; 

struct wpabuf * wpabuf_alloc(size_t len)
{
#ifdef WPA_TRACE
	struct wpabuf_trace *trace = os_zalloc(sizeof(struct wpabuf_trace) +
					       sizeof(struct wpabuf) + len);
	struct wpabuf *buf;
	if (trace == NULL)
		return NULL;
	trace->magic = WPABUF_MAGIC;
	buf = (struct wpabuf *) (trace + 1);
#else /* WPA_TRACE */
	struct wpabuf *buf = os_zalloc(sizeof(struct wpabuf) + len);
	if (buf == NULL)
		return NULL;
#endif /* WPA_TRACE */

	buf->size = len;
	buf->buf = (u8 *) (buf + 1);
	return buf;
}