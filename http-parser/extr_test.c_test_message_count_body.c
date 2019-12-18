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
struct message {char* name; int /*<<< orphan*/ * raw; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  message_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct message const*) ; 
 int num_messages ; 
 size_t parse_count_body (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_error (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

void
test_message_count_body (const struct message *message)
{
  parser_init(message->type);

  size_t read;
  size_t l = strlen(message->raw);
  size_t i, toread;
  size_t chunk = 4024;

  for (i = 0; i < l; i+= chunk) {
    toread = MIN(l-i, chunk);
    read = parse_count_body(message->raw + i, toread);
    if (read != toread) {
      print_error(message->raw, read);
      abort();
    }
  }


  read = parse_count_body(NULL, 0);
  if (read != 0) {
    print_error(message->raw, read);
    abort();
  }

  if (num_messages != 1) {
    printf("\n*** num_messages != 1 after testing '%s' ***\n\n", message->name);
    abort();
  }

  if(!message_eq(0, 0, message)) abort();
}