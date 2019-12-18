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
struct kill {int dummy; } ;
struct evbuffer {int dummy; } ;
typedef  scalar_t__ ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int evtag_unmarshal (struct evbuffer*,scalar_t__*,struct evbuffer*) ; 
 int kill_unmarshal (struct kill*,struct evbuffer*) ; 

int
evtag_unmarshal_kill(struct evbuffer *evbuf, ev_uint32_t need_tag, struct kill *msg)
{
  ev_uint32_t tag;
  int res = -1;

  struct evbuffer *tmp = evbuffer_new();

  if (evtag_unmarshal(evbuf, &tag, tmp) == -1 || tag != need_tag)
    goto error;

  if (kill_unmarshal(msg, tmp) == -1)
    goto error;

  res = 0;

 error:
  evbuffer_free(tmp);
  return (res);
}