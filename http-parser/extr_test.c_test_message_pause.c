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
struct message {char* name; scalar_t__ upgrade; int /*<<< orphan*/  type; scalar_t__ raw; } ;
struct TYPE_6__ {char* upgrade; scalar_t__ message_complete_cb_called; } ;
struct TYPE_5__ {scalar_t__ upgrade; } ;

/* Variables and functions */
 scalar_t__ HPE_PAUSED ; 
 scalar_t__ HPE_STRICT ; 
 scalar_t__ HTTP_PARSER_ERRNO (TYPE_1__*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  http_parser_pause (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct message const*) ; 
 TYPE_2__* messages ; 
 int num_messages ; 
 size_t parse_pause (char*,size_t) ; 
 TYPE_1__ parser ; 
 int /*<<< orphan*/  parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t strlen (scalar_t__) ; 

void
test_message_pause (const struct message *msg)
{
  char *buf = (char*) msg->raw;
  size_t buflen = strlen(msg->raw);
  size_t nread;

  parser_init(msg->type);

  do {
    nread = parse_pause(buf, buflen);

    // We can only set the upgrade buffer once we've gotten our message
    // completion callback.
    if (messages[0].message_complete_cb_called &&
        msg->upgrade &&
        parser.upgrade) {
      messages[0].upgrade = buf + nread;
      goto test;
    }

    if (nread < buflen) {

      // Not much do to if we failed a strict-mode check
      if (HTTP_PARSER_ERRNO(&parser) == HPE_STRICT) {
        return;
      }

      assert (HTTP_PARSER_ERRNO(&parser) == HPE_PAUSED);
    }

    buf += nread;
    buflen -= nread;
    http_parser_pause(&parser, 0);
  } while (buflen > 0);

  nread = parse_pause(NULL, 0);
  assert (nread == 0);

test:
  if (num_messages != 1) {
    printf("\n*** num_messages != 1 after testing '%s' ***\n\n", msg->name);
    abort();
  }

  if(!message_eq(0, 0, msg)) abort();
}