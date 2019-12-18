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
struct message {int /*<<< orphan*/  type; int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  buf1 ;
struct TYPE_4__ {int /*<<< orphan*/  headers_complete_cb_called; } ;
struct TYPE_3__ {size_t nread; scalar_t__ upgrade; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTTP_BOTH ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int count_parsed_messages (int,struct message const*,struct message const*,struct message const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  message_eq (int,int /*<<< orphan*/ ,struct message const*) ; 
 TYPE_2__* messages ; 
 int num_messages ; 
 size_t parse (char*,size_t) ; 
 TYPE_1__ parser ; 
 int /*<<< orphan*/  parser_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_error (char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strlncpy (char*,int,char*,size_t) ; 
 int /*<<< orphan*/  upgrade_message_fix (char*,size_t,int,struct message const*,struct message const*,struct message const*) ; 

void
test_scan (const struct message *r1, const struct message *r2, const struct message *r3)
{
  char total[80*1024] = "\0";
  char buf1[80*1024] = "\0";
  char buf2[80*1024] = "\0";
  char buf3[80*1024] = "\0";

  strcat(total, r1->raw);
  strcat(total, r2->raw);
  strcat(total, r3->raw);

  size_t read;

  int total_len = strlen(total);

  int total_ops = 2 * (total_len - 1) * (total_len - 2) / 2;
  int ops = 0 ;

  size_t buf1_len, buf2_len, buf3_len;
  int message_count = count_parsed_messages(3, r1, r2, r3);

  int i,j,type_both;
  for (type_both = 0; type_both < 2; type_both ++ ) {
    for (j = 2; j < total_len; j ++ ) {
      for (i = 1; i < j; i ++ ) {

        if (ops % 1000 == 0)  {
          printf("\b\b\b\b%3.0f%%", 100 * (float)ops /(float)total_ops);
          fflush(stdout);
        }
        ops += 1;

        parser_init(type_both ? HTTP_BOTH : r1->type);

        buf1_len = i;
        strlncpy(buf1, sizeof(buf1), total, buf1_len);
        buf1[buf1_len] = 0;

        buf2_len = j - i;
        strlncpy(buf2, sizeof(buf1), total+i, buf2_len);
        buf2[buf2_len] = 0;

        buf3_len = total_len - j;
        strlncpy(buf3, sizeof(buf1), total+j, buf3_len);
        buf3[buf3_len] = 0;

        assert(num_messages == 0);
        messages[0].headers_complete_cb_called = FALSE;

        read = parse(buf1, buf1_len);

        if (!messages[0].headers_complete_cb_called && parser.nread != read) {
          print_error(buf1, read);
          goto error;
        }

        if (parser.upgrade) goto test;

        if (read != buf1_len) {
          print_error(buf1, read);
          goto error;
        }

        read += parse(buf2, buf2_len);

        if (parser.upgrade) goto test;

        if (read != buf1_len + buf2_len) {
          print_error(buf2, read);
          goto error;
        }

        read += parse(buf3, buf3_len);

        if (parser.upgrade) goto test;

        if (read != buf1_len + buf2_len + buf3_len) {
          print_error(buf3, read);
          goto error;
        }

        parse(NULL, 0);

test:
        if (parser.upgrade) {
          upgrade_message_fix(total, read, 3, r1, r2, r3);
        }

        if (message_count != num_messages) {
          fprintf(stderr, "\n\nParser didn't see %d messages only %d\n",
            message_count, num_messages);
          goto error;
        }

        if (!message_eq(0, 0, r1)) {
          fprintf(stderr, "\n\nError matching messages[0] in test_scan.\n");
          goto error;
        }

        if (message_count > 1 && !message_eq(1, 0, r2)) {
          fprintf(stderr, "\n\nError matching messages[1] in test_scan.\n");
          goto error;
        }

        if (message_count > 2 && !message_eq(2, 0, r3)) {
          fprintf(stderr, "\n\nError matching messages[2] in test_scan.\n");
          goto error;
        }
      }
    }
  }
  puts("\b\b\b\b100%");
  return;

 error:
  fprintf(stderr, "i=%d  j=%d\n", i, j);
  fprintf(stderr, "buf1 (%u) %s\n\n", (unsigned int)buf1_len, buf1);
  fprintf(stderr, "buf2 (%u) %s\n\n", (unsigned int)buf2_len , buf2);
  fprintf(stderr, "buf3 (%u) %s\n", (unsigned int)buf3_len, buf3);
  abort();
}