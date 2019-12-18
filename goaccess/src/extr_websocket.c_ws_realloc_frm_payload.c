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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ payloadsz; char* payload; } ;
typedef  TYPE_1__ WSMessage ;
struct TYPE_6__ {scalar_t__ payloadlen; } ;
typedef  TYPE_2__ WSFrame ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* realloc (char*,scalar_t__) ; 

__attribute__((used)) static int
ws_realloc_frm_payload (WSFrame * frm, WSMessage * msg)
{
  char *tmp = NULL;
  uint64_t newlen = 0;

  newlen = msg->payloadsz + frm->payloadlen;
  tmp = realloc (msg->payload, newlen);
  if (tmp == NULL && newlen > 0) {
    free (msg->payload);
    msg->payload = NULL;
    return 1;
  }
  msg->payload = tmp;

  return 0;
}