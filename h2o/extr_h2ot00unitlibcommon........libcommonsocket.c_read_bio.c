#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* ssl; } ;
typedef  TYPE_3__ h2o_socket_t ;
struct TYPE_9__ {int size; int /*<<< orphan*/  bytes; } ;
struct TYPE_6__ {TYPE_4__* encrypted; } ;
struct TYPE_7__ {TYPE_1__ input; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 TYPE_3__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_4__**,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_bio(BIO *b, char *out, int len)
{
    h2o_socket_t *sock = BIO_get_data(b);

    if (len == 0)
        return 0;

    if (sock->ssl->input.encrypted->size == 0) {
        BIO_set_retry_read(b);
        return -1;
    }

    if (sock->ssl->input.encrypted->size < len) {
        len = (int)sock->ssl->input.encrypted->size;
    }
    memcpy(out, sock->ssl->input.encrypted->bytes, len);
    h2o_buffer_consume(&sock->ssl->input.encrypted, len);

    return len;
}