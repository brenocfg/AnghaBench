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
struct connection {int /*<<< orphan*/  In; } ;
struct TYPE_3__ {int readed; int /*<<< orphan*/  len; scalar_t__ extra; } ;
typedef  TYPE_1__ data_reader_t ;

/* Variables and functions */
 int /*<<< orphan*/  read_in (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

void data_read_conn (data_reader_t *reader, void *dest) {
  reader->readed = 1;
  read_in (&((struct connection *)(reader->extra))->In, dest, reader->len);
}