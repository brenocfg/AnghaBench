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
struct wpabuf_trace {scalar_t__ magic; int flags; struct wpabuf_trace* buf; } ;
struct wpabuf {scalar_t__ magic; int flags; struct wpabuf* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int WPABUF_FLAG_EXT_DATA ; 
 scalar_t__ WPABUF_MAGIC ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  os_free (struct wpabuf_trace*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_trace_show (char*) ; 
 struct wpabuf_trace* wpabuf_get_trace (struct wpabuf_trace*) ; 

void wpabuf_free(struct wpabuf *buf)
{
#ifdef WPA_TRACE
	struct wpabuf_trace *trace;
	if (buf == NULL)
		return;
	trace = wpabuf_get_trace(buf);
	if (trace->magic != WPABUF_MAGIC) {
		wpa_printf(MSG_ERROR, "wpabuf_free: invalid magic %x",
			   trace->magic);
		wpa_trace_show("wpabuf_free magic mismatch");
		abort();
	}
	if (buf->flags & WPABUF_FLAG_EXT_DATA)
		os_free(buf->buf);
	os_free(trace);
#else /* WPA_TRACE */
	if (buf == NULL)
		return;
	if (buf->flags & WPABUF_FLAG_EXT_DATA)
		os_free(buf->buf);
	os_free(buf);
#endif /* WPA_TRACE */
}