#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hm_header_st {int /*<<< orphan*/  frag_len; int /*<<< orphan*/  frag_off; int /*<<< orphan*/  seq; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__* d1; } ;
struct TYPE_4__ {struct hm_header_st w_msg_hdr; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  l2n3 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  s2n (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static unsigned char *dtls1_write_message_header(SSL *s, unsigned char *p)
{
    struct hm_header_st *msg_hdr = &s->d1->w_msg_hdr;

    *p++ = msg_hdr->type;
    l2n3(msg_hdr->msg_len, p);

    s2n(msg_hdr->seq, p);
    l2n3(msg_hdr->frag_off, p);
    l2n3(msg_hdr->frag_len, p);

    return p;
}