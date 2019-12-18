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
struct repl_server_status {char* buffer; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */

inline unsigned char load_byte (struct repl_server_status *S, char **ptr) {
  --*ptr;
  if (*ptr < S->buffer) {
    *ptr += S->buffer_size;
  }
  return (unsigned char)**ptr;
}