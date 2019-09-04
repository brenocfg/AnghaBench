#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_poll_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_8__ {int events; int read; int got_fin; int delayed_events; scalar_t__ sent; int sent_fin; int got_disconnect; int /*<<< orphan*/  sock; TYPE_1__ poll_handle; int /*<<< orphan*/  timer_handle; scalar_t__ is_server_connection; } ;
typedef  TYPE_2__ connection_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  SHUT_WR ; 
 scalar_t__ TRANSFER_BYTES ; 
 scalar_t__ UNIDIRECTIONAL ; 
 int UV_DISCONNECT ; 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 int /*<<< orphan*/  close_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay_timer_cb ; 
 int /*<<< orphan*/  destroy_connection_context (TYPE_2__*) ; 
 int /*<<< orphan*/  disconnects ; 
 int got_eagain () ; 
 int rand () ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spurious_writable_wakeups ; 
 scalar_t__ test_mode ; 
 int uv_is_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_poll_start (TYPE_1__*,unsigned int,void (*) (TYPE_1__*,int,int)) ; 
 int /*<<< orphan*/  uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_writable_wakeups ; 

__attribute__((used)) static void connection_poll_cb(uv_poll_t* handle, int status, int events) {
  connection_context_t* context = (connection_context_t*) handle->data;
  unsigned int new_events;
  int r;

  ASSERT(status == 0);
  ASSERT(events & context->events);
  ASSERT(!(events & ~context->events));

  new_events = context->events;

  if (events & UV_READABLE) {
    int action = rand() % 7;

    switch (action) {
      case 0:
      case 1: {
        /* Read a couple of bytes. */
        static char buffer[74];
        r = recv(context->sock, buffer, sizeof buffer, 0);
        ASSERT(r >= 0);

        if (r > 0) {
          context->read += r;
        } else {
          /* Got FIN. */
          context->got_fin = 1;
          new_events &= ~UV_READABLE;
        }

        break;
      }

      case 2:
      case 3: {
        /* Read until EAGAIN. */
        static char buffer[931];
        r = recv(context->sock, buffer, sizeof buffer, 0);
        ASSERT(r >= 0);

        while (r > 0) {
          context->read += r;
          r = recv(context->sock, buffer, sizeof buffer, 0);
        }

        if (r == 0) {
          /* Got FIN. */
          context->got_fin = 1;
          new_events &= ~UV_READABLE;
        } else {
          ASSERT(got_eagain());
        }

        break;
      }

      case 4:
        /* Ignore. */
        break;

      case 5:
        /* Stop reading for a while. Restart in timer callback. */
        new_events &= ~UV_READABLE;
        if (!uv_is_active((uv_handle_t*) &context->timer_handle)) {
          context->delayed_events = UV_READABLE;
          uv_timer_start(&context->timer_handle, delay_timer_cb, 10, 0);
        } else {
          context->delayed_events |= UV_READABLE;
        }
        break;

      case 6:
        /* Fudge with the event mask. */
        uv_poll_start(&context->poll_handle, UV_WRITABLE, connection_poll_cb);
        uv_poll_start(&context->poll_handle, UV_READABLE, connection_poll_cb);
        context->events = UV_READABLE;
        break;

      default:
        ASSERT(0);
    }
  }

  if (events & UV_WRITABLE) {
    if (context->sent < TRANSFER_BYTES &&
        !(test_mode == UNIDIRECTIONAL && context->is_server_connection)) {
      /* We have to send more bytes. */
      int action = rand() % 7;

      switch (action) {
        case 0:
        case 1: {
          /* Send a couple of bytes. */
          static char buffer[103];

          int send_bytes = MIN(TRANSFER_BYTES - context->sent, sizeof buffer);
          ASSERT(send_bytes > 0);

          r = send(context->sock, buffer, send_bytes, 0);

          if (r < 0) {
            ASSERT(got_eagain());
            spurious_writable_wakeups++;
            break;
          }

          ASSERT(r > 0);
          context->sent += r;
          valid_writable_wakeups++;
          break;
        }

        case 2:
        case 3: {
          /* Send until EAGAIN. */
          static char buffer[1234];

          int send_bytes = MIN(TRANSFER_BYTES - context->sent, sizeof buffer);
          ASSERT(send_bytes > 0);

          r = send(context->sock, buffer, send_bytes, 0);

          if (r < 0) {
            ASSERT(got_eagain());
            spurious_writable_wakeups++;
            break;
          }

          ASSERT(r > 0);
          valid_writable_wakeups++;
          context->sent += r;

          while (context->sent < TRANSFER_BYTES) {
            send_bytes = MIN(TRANSFER_BYTES - context->sent, sizeof buffer);
            ASSERT(send_bytes > 0);

            r = send(context->sock, buffer, send_bytes, 0);

            if (r <= 0) break;
            context->sent += r;
          }
          ASSERT(r > 0 || got_eagain());
          break;
        }

        case 4:
          /* Ignore. */
         break;

        case 5:
          /* Stop sending for a while. Restart in timer callback. */
          new_events &= ~UV_WRITABLE;
          if (!uv_is_active((uv_handle_t*) &context->timer_handle)) {
            context->delayed_events = UV_WRITABLE;
            uv_timer_start(&context->timer_handle, delay_timer_cb, 100, 0);
          } else {
            context->delayed_events |= UV_WRITABLE;
          }
          break;

        case 6:
          /* Fudge with the event mask. */
          uv_poll_start(&context->poll_handle,
                        UV_READABLE,
                        connection_poll_cb);
          uv_poll_start(&context->poll_handle,
                        UV_WRITABLE,
                        connection_poll_cb);
          context->events = UV_WRITABLE;
          break;

        default:
          ASSERT(0);
      }

    } else {
      /* Nothing more to write. Send FIN. */
      int r;
#ifdef _WIN32
      r = shutdown(context->sock, SD_SEND);
#else
      r = shutdown(context->sock, SHUT_WR);
#endif
      ASSERT(r == 0);
      context->sent_fin = 1;
      new_events &= ~UV_WRITABLE;
    }
  }
#if !defined(__sun) && !defined(_AIX) && !defined(__MVS__)
  if (events & UV_DISCONNECT) {
    context->got_disconnect = 1;
    ++disconnects;
    new_events &= ~UV_DISCONNECT;
  }

  if (context->got_fin && context->sent_fin && context->got_disconnect) {
#else /* __sun && _AIX  && __MVS__ */
  if (context->got_fin && context->sent_fin) {
#endif /* !__sun && !_AIX && !__MVS__  */
    /* Sent and received FIN. Close and destroy context. */
    close_socket(context->sock);
    destroy_connection_context(context);
    context->events = 0;

  } else if (new_events != context->events) {
    /* Poll mask changed. Call uv_poll_start again. */
    context->events = new_events;
    uv_poll_start(handle, new_events, connection_poll_cb);
  }

  /* Assert that uv_is_active works correctly for poll handles. */
  if (context->events != 0) {
    ASSERT(1 == uv_is_active((uv_handle_t*) handle));
  } else {
    ASSERT(0 == uv_is_active((uv_handle_t*) handle));
  }
}