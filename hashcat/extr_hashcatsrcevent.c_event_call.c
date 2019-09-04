#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* event ) (int const,TYPE_1__*,void const*,size_t const) ;TYPE_2__* event_ctx; } ;
typedef  TYPE_1__ hashcat_ctx_t ;
struct TYPE_6__ {void const** old_buf; size_t* old_len; int /*<<< orphan*/  mux_event; } ;
typedef  TYPE_2__ event_ctx_t ;

/* Variables and functions */
#define  EVENT_LOG_ADVICE 131 
#define  EVENT_LOG_ERROR 130 
#define  EVENT_LOG_INFO 129 
#define  EVENT_LOG_WARNING 128 
 int MAX_OLD_EVENTS ; 
 size_t MIN (size_t const,size_t const) ; 
 int /*<<< orphan*/  hc_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int const,TYPE_1__*,void const*,size_t const) ; 

void event_call (const u32 id, hashcat_ctx_t *hashcat_ctx, const void *buf, const size_t len)
{
  event_ctx_t *event_ctx = hashcat_ctx->event_ctx;

  bool is_log = false;

  switch (id)
  {
    case EVENT_LOG_INFO:    is_log = true; break;
    case EVENT_LOG_WARNING: is_log = true; break;
    case EVENT_LOG_ERROR:   is_log = true; break;
    case EVENT_LOG_ADVICE:  is_log = true; break;
  }

  if (is_log == false)
  {
    hc_thread_mutex_lock (event_ctx->mux_event);
  }

  hashcat_ctx->event (id, hashcat_ctx, buf, len);

  if (is_log == false)
  {
    hc_thread_mutex_unlock (event_ctx->mux_event);
  }

  // add more back logs in case user wants to access them

  if (is_log == false)
  {
    for (int i = MAX_OLD_EVENTS - 1; i >= 1; i--)
    {
      memcpy (event_ctx->old_buf[i], event_ctx->old_buf[i - 1], event_ctx->old_len[i - 1]);

      event_ctx->old_len[i] = event_ctx->old_len[i - 1];
    }

    size_t copy_len = 0;

    if (buf)
    {
      // truncate the whole buffer if needed (such that it fits into the old_buf):

      const size_t max_buf_len = sizeof (event_ctx->old_buf[0]);

      copy_len = MIN (len, max_buf_len - 1);

      memcpy (event_ctx->old_buf[0], buf, copy_len);
    }

    event_ctx->old_len[0] = copy_len;
  }
}