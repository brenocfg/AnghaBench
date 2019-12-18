#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hEvent; } ;
struct wpa_global_dst {scalar_t__ pipe; struct wpa_global_dst* rsp_buf; TYPE_3__* prev; TYPE_2__* next; TYPE_1__* priv; TYPE_4__ overlap; } ;
struct TYPE_7__ {TYPE_2__* next; } ;
struct TYPE_6__ {TYPE_3__* prev; } ;
struct TYPE_5__ {TYPE_2__* ctrl_dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_unregister_event (scalar_t__,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_global_dst*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wpa_global_dst*) ; 

__attribute__((used)) static void global_close_pipe(struct wpa_global_dst *dst)
{
	wpa_printf(MSG_DEBUG, "CTRL: close pipe %p", dst);

	if (dst->overlap.hEvent) {
		eloop_unregister_event(dst->overlap.hEvent,
				       sizeof(dst->overlap.hEvent));
		CloseHandle(dst->overlap.hEvent);
	}

	if (dst->pipe != INVALID_HANDLE_VALUE) {
		/*
		 * Could use FlushFileBuffers() here to guarantee that all data
		 * gets delivered to the client, but that can block, so let's
		 * not do this for now.
		 * FlushFileBuffers(dst->pipe);
		 */
		CloseHandle(dst->pipe);
	}

	if (dst->prev)
		dst->prev->next = dst->next;
	else
		dst->priv->ctrl_dst = dst->next;
	if (dst->next)
		dst->next->prev = dst->prev;

	os_free(dst->rsp_buf);
	os_free(dst);
}