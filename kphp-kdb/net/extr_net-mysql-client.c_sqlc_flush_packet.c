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
struct connection {int /*<<< orphan*/  Out; TYPE_1__* type; scalar_t__ crypto; } ;
struct TYPE_4__ {int block_size; } ;
struct TYPE_3__ {int (* crypto_needed_output_bytes ) (struct connection*) ;} ;

/* Variables and functions */
 TYPE_2__* SQLC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (struct connection*) ; 
 int verbosity ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int) ; 

int sqlc_flush_packet (struct connection *c, int packet_len) {
  int pad_bytes = 0;
  if (c->crypto) {
    pad_bytes = c->type->crypto_needed_output_bytes (c);
    if (packet_len >= 0) {
      int b = SQLC_DATA(c)->block_size;
      packet_len += 4;
      packet_len = b - packet_len % b;
      if (packet_len == b) {
        packet_len = 0;
      }
      assert (packet_len == pad_bytes);
    }
    if (verbosity > 1) {
      fprintf (stderr, "sqlc_flush_query: padding with %d bytes\n", pad_bytes);
    }
    if (pad_bytes > 0) {
      static char pad_str[16];
      assert (pad_bytes <= 15);
      memset (pad_str, pad_bytes, pad_bytes);
      write_out (&c->Out, pad_str, pad_bytes);
    }
  }
  return pad_bytes;
}