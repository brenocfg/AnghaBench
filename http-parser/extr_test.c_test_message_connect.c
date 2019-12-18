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
struct message {char* name; int /*<<< orphan*/  type; scalar_t__ raw; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  message_eq (int /*<<< orphan*/ ,int,struct message const*) ; 
 int num_messages ; 
 int /*<<< orphan*/  parse_connect (char*,size_t) ; 
 int /*<<< orphan*/  parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t strlen (scalar_t__) ; 

void
test_message_connect (const struct message *msg)
{
  char *buf = (char*) msg->raw;
  size_t buflen = strlen(msg->raw);

  parser_init(msg->type);

  parse_connect(buf, buflen);

  if (num_messages != 1) {
    printf("\n*** num_messages != 1 after testing '%s' ***\n\n", msg->name);
    abort();
  }

  if(!message_eq(0, 1, msg)) abort();
}