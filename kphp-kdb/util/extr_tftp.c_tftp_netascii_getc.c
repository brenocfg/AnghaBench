#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  name; int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {TYPE_2__* netascii; TYPE_1__ file; } ;
typedef  TYPE_3__ tftp_connection_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {int unflushed_char; scalar_t__ rptr; scalar_t__ size; unsigned char* iobuff; } ;

/* Variables and functions */
 int /*<<< orphan*/  TFTP_IOBUFF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ read (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tftp_netascii_getc (tftp_connection_t *c) {
  unsigned char d;
  if (c->netascii->unflushed_char != 255) {
    d = c->netascii->unflushed_char;
    c->netascii->unflushed_char = 255;
    return d;
  }
  if (c->netascii->rptr >= c->netascii->size) {
    ssize_t r = read (c->file.fd, c->netascii->iobuff, TFTP_IOBUFF_SIZE);
    if (r < 0) {
      vkprintf (1, "Fail to read file '%s' from offset %lld. %m\n", c->file.name, c->file.pos);
      return -2;
    }
    c->file.pos += r;
    c->netascii->size = r;
    c->netascii->rptr = 0;
    if (!r) {
      return -1; /* EOF */
    }
  }
  assert (c->netascii->rptr < c->netascii->size);
  d = c->netascii->iobuff[c->netascii->rptr++];
  if (d == '\n') {
    c->netascii->unflushed_char = '\n';
    return '\r';
  }
  if (d == '\r') {
    c->netascii->unflushed_char = 0;
    return '\r';
  }
  return d;
}