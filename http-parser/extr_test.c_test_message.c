#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct message {char* raw; char* name; scalar_t__ upgrade; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {char const* upgrade; int /*<<< orphan*/  headers_complete_cb_called; } ;
struct TYPE_3__ {size_t nread; scalar_t__ upgrade; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  message_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct message const*) ; 
 TYPE_2__* messages ; 
 int num_messages ; 
 size_t parse (char const*,size_t) ; 
 TYPE_1__ parser ; 
 int /*<<< orphan*/  parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_error (char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t strlen (char*) ; 

void
test_message (const struct message *message)
{
  size_t raw_len = strlen(message->raw);
  size_t msg1len;
  for (msg1len = 0; msg1len < raw_len; msg1len++) {
    parser_init(message->type);

    size_t read;
    const char *msg1 = message->raw;
    const char *msg2 = msg1 + msg1len;
    size_t msg2len = raw_len - msg1len;

    if (msg1len) {
      assert(num_messages == 0);
      messages[0].headers_complete_cb_called = FALSE;

      read = parse(msg1, msg1len);

      if (!messages[0].headers_complete_cb_called && parser.nread != read) {
        assert(parser.nread == read);
        print_error(msg1, read);
        abort();
      }

      if (message->upgrade && parser.upgrade && num_messages > 0) {
        messages[num_messages - 1].upgrade = msg1 + read;
        goto test;
      }

      if (read != msg1len) {
        print_error(msg1, read);
        abort();
      }
    }


    read = parse(msg2, msg2len);

    if (message->upgrade && parser.upgrade) {
      messages[num_messages - 1].upgrade = msg2 + read;
      goto test;
    }

    if (read != msg2len) {
      print_error(msg2, read);
      abort();
    }

    read = parse(NULL, 0);

    if (read != 0) {
      print_error(message->raw, read);
      abort();
    }

  test:

    if (num_messages != 1) {
      printf("\n*** num_messages != 1 after testing '%s' ***\n\n", message->name);
      abort();
    }

    if(!message_eq(0, 0, message)) abort();
  }
}