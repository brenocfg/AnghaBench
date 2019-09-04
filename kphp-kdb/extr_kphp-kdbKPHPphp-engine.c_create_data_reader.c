#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_3__ {int len; int /*<<< orphan*/  read; struct connection* extra; scalar_t__ readed; } ;
typedef  TYPE_1__ data_reader_t ;

/* Variables and functions */
 int /*<<< orphan*/  data_read_conn ; 

data_reader_t *create_data_reader (struct connection *c, int data_len) {
  static data_reader_t reader;

  reader.readed = 0;
  reader.len = data_len;
  reader.extra = c;

  reader.read = data_read_conn;

  return &reader;
}